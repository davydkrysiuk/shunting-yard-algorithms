input = "2 + ( 2 * ( 2 * ( 2 + 4 * ( 1 + 2 ) ) ) )"
input = input.split()

out_queue = []
op_stack = []

def precedence(operator):
    if operator == '+' or operator == '-':
        return 1
    elif operator == '*' or operator == '/':
        return 2
    elif operator == '^':
        return 3
    else:
        return 0

for tok in input:
    if tok.isnumeric():
        out_queue.append(int(tok))
    elif tok in ('+', '-', '*', '/'):
        while op_stack and precedence(op_stack[-1]) >= precedence(tok):
            out_queue.append(op_stack.pop())
        op_stack.append(tok)
    elif tok == '(':
        op_stack.append(tok)
    elif tok == ')':
        while op_stack and op_stack[-1] != '(':
            out_queue.append(op_stack.pop())
        op_stack.pop()

while op_stack:
    out_queue.append(op_stack.pop())

def applyop(o2, o1, tk):
    o1 = float(o1)
    o2 = float(o2)
    if tk == '+':
        return o1 + o2
    elif tk == '-':
        return o1 - o2
    elif tk == '*':
        return o1 * o2
    elif tk == '/':
        return o1 / o2
    
def evalpfx(pfx):
    stack = []
    for token in pfx:
        if isinstance(token, int):
            stack.append(token)
        else:
            op_2 = stack.pop()
            op_1 = stack.pop()
            result = applyop(op_2, op_1, token)
            stack.append(result)
    return stack.pop()

print(evalpfx(out_queue))

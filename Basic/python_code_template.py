# python code template for OJ.
import traceback
try:
    while True:
        s = input()
except EOFError:
    pass
except Exception as e:
    traceback.print_exc(e)
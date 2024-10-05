def my_function(param1, param2):
    result = param1 + param2
    if result > 10:
        print("Result is greater than 10")
    else:
        print("Result is 10 or less")
    return result


class MyClass:
    def __init__(self, value):
        self.value = value

    def display(self):
        print("Value:", self.value)

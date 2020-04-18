@shared_task
def add(x, y):
    print "Add task called"
    return x + y


@shared_task
def mul(x, y):
    print "Mul task called"
    return x * y


@shared_task
def xsum(numbers):
    print "xsum task called"
    return sum(numbers)

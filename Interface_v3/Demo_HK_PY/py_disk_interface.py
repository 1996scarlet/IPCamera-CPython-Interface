import os

def new_report(test_report):
    lists = os.listdir(test_report)
    print(list)
    lists.sort(key=lambda fn:os.path.getmtime(test_report + "\\" + fn))
    file_new = os.path.join(test_report,lists[-1])
    print(file_new)
    return file_new

if __name__=="__main__":
    new_report("./result")
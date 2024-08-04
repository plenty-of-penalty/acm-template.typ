from time import sleep

def typst_build():
    pass

def typst_watch():
    pass

def build_source():
    pass

def build():
    build_source()
    typst_build()

def watch():
    typst_watch()
    while True:
        build_source()
        sleep(5)

if __name__ == '__main__':
    build()
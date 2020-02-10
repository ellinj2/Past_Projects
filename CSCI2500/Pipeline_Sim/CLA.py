# -*- coding: utf-8 -*-
"""
Created on Fri Dec  6 10:25:30 2019

@author: Xerox
"""

import sys

#ERROR CHECKING FOR OUR CONVENIENCE. UNNECCESSARY ON SUBMISSION
def run_error_check():
    if len(sys.argv) < 3:
        print("Too few arguments.")
        sys.exit()
    elif len(sys.argv) > 3:
        print("Too many arguments.")
        sys.exit()
        
    if(sys.argv[1] not in ("N", "F")):
        print("Cannot parse forwarding input")
        sys.exit()
    try:
        f = open(sys.argv[2])
    except FileNotFoundError:
        print("Invalid filename")
    finally:
        f.close()


if __name__ == "__main__":
    
    run_error_check()
    print("It worked!")

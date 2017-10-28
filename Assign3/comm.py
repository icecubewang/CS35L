#!/usr/bin/python

import sys, locale, random, string
from optparse import OptionParser

class comm:
    def __init__(self, args, first_col, second_col, third_col, unsorted):
      #  if args[0] == "-":
      #      self.lines1 = sys.stdin.readlines()
      #  else:
      #      f1 = open(args[0], 'r')
#        self.lines1 = f1.readlines()
      #      f1.close()
      #  if args[1] == "-":
      #      self.lines2 = sys.stdin.readlines()
      #  else:
      #      f2 = open(args[1], 'r')
#        self.lines2 = f2.readlines()
      #      f2.close()

        self.first_col = first_col
        self.second_col = second_col
        self.third_col = third_col
        self.unsorted = unsorted
       # self.lines1 = self.appendNewline(self.lines1)
       # self.lines2 = self.appendNewline(self.lines2)

        try:
            if args[0] == "-":
                f1 = sys.stdin.readlines()
                f2 = open(args[1],'r')
            elif args[1] == "-":
                f1 = open(args[0], 'r')
                f2 = sys.stdin.readlines()
#            elif args[0] == "-" and args[1] == "-":
#                parser.error("Cannot read both files from standard inputs")
            else:
                f1 = open(args[0], 'r')
                f2 = open(args[1], 'r')

#            self.lines1 = f1.read().split('\n')
#            self.lines2 = f2.read().split('\n')
#            del self.lines1[len(self.lines1)-1]
#            del self.lines2[len(self.lines2)-1]
            self.lines1 = f1.readlines()
            self.lines2 = f2.readlines()
            self.lines1 = self.appendNewline(self.lines1)
            self.lines2 = self.appendNewline(self.lines2)
            
            f1.close()
            f2.close()

        except IOError as err:
            errno = err.errno
            strerror = e.strerror
            parser.error("I/O error({0}):{1}".format(errno, strerror))

    def appendNewline(self, file):
        if not len(file):
            file.append("\n")
        else:
            temp = file[-1]
            if "\n" not in temp:
                temp += "\n"
            file[-1] = temp
        return file

#        for i in range(len(file)):
#            if file[i] == '':
#                file[i] = '\n'
#            if file[i].count(' ') >= 1 and file[i].isspace():
#                file[i] = '\n' * file[i].count(' ')

    def writeline(self, givenline, column):
        formline = ""
        if column == 1:
            if not self.first_col:
                return
        elif column == 2:
            if not self.second_col:
                return
            if self.first_col:
                formline += "\t"
        elif column == 3:
            if not self.third_col:
                return
            if self.first_col:
                formline += "\t"
            if self.second_col:
                formline += "\t"
        else:
            sys.stderr.write("Incorrect argument for suppressing!\n")
        sys.stdout.write(formline + givenline)

    def issorted(self, file, index):
#        sorted_line1, sorted_line2 = sorted(self.lines1), sorted(self.lines2)
#        files_sorted = True

#        if sorted_line1 != self.lines1:
#            files_sorted = False
#            sys.stderr.write("FILE1 not sorted!\n")
        
#        if sorted_line2 != self.lines2:
#            files_sorted = False
#            sys.stderr.write("FILE2 not sorted!\n")

#        return files_sorted

        for i in range(len(file) - 1):
            if locale.strcoll(file[i], file[i+1]) > 0:
                print("FILE %s not sorted\n") % file
                exit()
        return True

    def compare_files(self):
        if self.unsorted:
            diff_line2 = self.lines2
            for line1 in self.lines1:
                if line1 not in self.lines2:
                    self.writeline(line1, int(1))
                else:
                    self.writeline(line1, int(3))
                    diff_line2.remove(line1)

            for line2 in diff_line2:
                self.writeline(line2, int(2))
            return

        if not self.issorted(self.lines1, 1) and self.issorted(self.lines2, 2):
            return

        i, j = 0, 0
        while i in range(self.lines1) or j in range(self.lines2):
            line1, line2 = "", ""
        
            if i < self.lines1:
                line1 = self.lines1[i]
            if j < self.lines2:
                line2 = self.lines2[j]

            if line1 == "" or (line2 != "" and line1 > line2):
                self.writeline(line2, 2)
                j += 1
            elif line2 == "" or line1 < line2:
                self.writeline(line1, 1)
                i += 1
            else:
                self.writeline(line2, 3)
                i += 1
                j += 1
        return


def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2
Compare files FILE1 and FILE2,
and produce three text columns as output:
1: lines only in FILE1
2: lines only in FILE2
3: lines in both FILE1 and FILE2
"""

    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-1", "--nofile1", dest="first_col", action="store_false",
                      default=True, help="suppress column 1")
    parser.add_option("-2", "--nofile2", dest="second_col", action="store_false",
                      default=True, help="suppress column 2")
    parser.add_option("-3", "--nocommonfile", dest="third_col", action="store_false",
                      default=True, help="suppress column 3")
    parser.add_option("-u", "--unsorted", dest="unsorted", action="store_true",
                      default=False, help="unsorted files")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        first_col = bool(options.first_col)
        second_col = bool(options.second_col)
        third_col = bool(options.third_col)
        unsorted = bool(options.unsorted)
    except:
        parser.error("invalid argument for option: {0}".format(options.unsorted))

    if len(args) != 2:
        parser.error("Wrong number of operands")

    if args[0] == "-" and args[1] == "-":
        parser.error("Cannot read both files from standard input!")

    try:
        generator = comm(args, first_col, second_col, third_col, unsorted)
        generator.compare_files()
    except OSError as err:
        errno = err.errno
        strerror = err.strerror
        parser.error("I/O error({0}):{1}".format(error, strerror))
    
if __name__ == "__main__":
    main()

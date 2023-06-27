# File Operations | C

In this project, the goal is to scan a target folder and its subfolders, access the text files within those folders, and perform various operations on those files.
The scanning process is based on the "file tag" system. For a word to be a "tag," it must conform to the label structure (enclosed by [[-]] brackets) within the text 
files, or it must be the name of a text file itself. The labels are classified into two groups:

Orphan Labels: If a label appears in a text but does not have its own corresponding text file, it is considered an orphan label.

Desired Labels: If the name of a text file does not appear in any text, it is considered a desired label.

The user can create a text file through the menu interface. When creating a file, it is saved inside the "class names" subfolder according to the format of other lessons,
starting the numbering from 200. The user can also delete an existing text file. Additionally, the user can search for a word/phrase within the text files. If a match is found during
the search,the line and file information will be displayed. The user can also rename a label, which can be a desired label or an orphan label. The renaming process affects all 
files simultaneously.
When exiting the project, the tag information and their occurrence counts are displayed on the screen, and the tags are classified. Additionally, this information
is saved to a text file named "output.txt".

![c](https://github.com/baranulkun/fileOperations/assets/74157174/39bf28ac-1ed3-4268-a692-5de007e9ef64)

How this works: "https://youtu.be/0gu0tQKgQbA"

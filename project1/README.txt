Name: Kevin Haynie
Date: 1/18/2014
Project: 1
Filename: README

Usage (with included makefile):
make          -- build application binary
make clean    -- clean binary and object files created by make
./imgview     -- Launch application in "Default" mode with no image specified.
                 This will create a base window of DEFWIDTH and DEFHEIGHT as defined
                 in imgview.h and wait for user input.  Valid inputs are: 'r' or 'R',
                 which prompts the user for an image filename to read and view.  'w'
                 or 'W' promps the user for an image filename to write the current
                 view to.  Finally, 'q', 'Q', or the 'esc' key will exit the application.
./imgview <filename>
              -- Similar to the above, this provides the application with an initial
                 image to load at execution to replace the default window parameters.
                 Otherwise, all functionality remains the same as above.

In application keyboard commands:

'q','Q','esc' -- Terminate application
'w','W'       -- Prompt user for filename to write current image out to
'r','R'       -- Prompt user for filename to read image in from

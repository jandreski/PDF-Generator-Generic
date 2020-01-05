# PDF Generator
**README file is still WIP**

This is a Qt5 based application that takes a group of people and a mailing template, and generates a *.tex* file which can then be converted to a pdf. The generated PDF is a standard in standard german form.  
The application has been tested on Windows 10, but should ideally work for earlier versions of Windows as well.

# How to compile
WIP!

# How to use
Upon executing the program, the following should appear:

![Main Window Screenshot](/data/other/main_window.png)

Then, fill in all the slots. Click "Veranstaltung Einstellungen" (Event settings) to configure the event you've selected.  
A filled instance would like so:

![Main Window Filled Screenshot](/data/other/main_window_filled.png)

Lastly, click **Generate PDF**. This will create the file **finalPDF.tex** in the data folder. Please copy this file, as well as all the signatures that can be found in: *<application directory>/data/unterschriften/*, and put them in the same folder. Then, the pdf can be generated either online or offline.
  
A sample PDF can be seen [here](/data/other/example_pdf.pdf "Example PDF")

# How to update data
### Using the GUI
| How to update        | Explanation   |
| :-------------: |:-------------:|
| **Members signing the documents** | Click on "Einstellungen", and edit the data there |
| **Event specific data** | Click on "Veranstaltung Einstellungen", and edit the data there |

### Using the "data" folder
| How to update        | Explanation   |
| :-------------: |:-------------:|
| **Event templates** | Go to */data/templates/* and edit the respective **editMe.txt** files |
| **Preview PDFs** | Go to */data/templates/* and change out the respective **Sample.pdf** files |
| **Schedule template** | This template only affect Event 2. Go to */data/intermediate/schedule_template.txt*, to edit the template |

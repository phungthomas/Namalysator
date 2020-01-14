# BnL Quality Control Tool

This project is the initial QA tool that has been developed at the BnL in 2014 and is still in use for current digitization compaigns.
However, the software is not actively developed. Only severe bug fixes are being made. The last major update was in 2018.

The software is written in C++ and consist of 3 programs:

* `loadinventory`: Load an external inventory file.
* `metsverifier`: Verifies a batch containing METS/ALTO packages.
* `namalysator`: GUI for quality control.

## Features

* BNL Inventory loading
* METS/ALTO validation against BnL Schema
* Various logical checks (Page numbers, inventory cross-validation)
* GUI with calendar view, document listing, error listing and document viewer.
* Error reporting and exporting


# Dependencies / Requirements

* Windows 7 or later
* Visual Studio (recommended)
* QT 4.x (to be compiled from sources)
* Other C++ libraries might have to be compiled from source as well (Xalan, Xerces, Boost)

*Note:*

To compile this project, several paths linked to `C:\` might have to be updated for your local development environment.

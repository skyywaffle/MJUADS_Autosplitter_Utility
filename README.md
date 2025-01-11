# MJUADS Autosplitter Utility
A utility to configure autosplitting for Monster Jam: Urban Assault DS

## How does it work?
[ShootMe's DeSmuME Autosplitter component](https://github.com/ShootMe/LiveSplit.DeSmuME) works with LiveSplit and DeSmuME's memory to accurately split based on checking game addresses. However, this is only possible by configuring it to your layout, which is both tedious and can go wrong easily. This utility automates that process and (hopefully) works 100% of the time!

## Disclaimers
- This autosplitter only supports DeSmuME 0.9.11.
- Version Alpha 1 only has support for game region USA and Speedster% category.
- Since this project is currently not fully developed, please copy your LiveSplit layout file somewhere else before using the program, because the program directly modifies your layout file.
- Change your split file to start at 0.20 seconds for the timing to be as accurate as possible with manual retiming.

## Usage
- Download [LiveSplit.DeSmuME.dll](https://raw.githubusercontent.com/ShootMe/LiveSplit.DeSmuME/master/Components/LiveSplit.DeSmuME.dll) and place it in the LiveSplit/Components directory. In the future I may add an auto-downloader for it.
- Download MJUADS_Autosplitter_Utility.exe from the [Releases](https://github.com/skyywaffle/MJUADS_Autosplitter_Utility/releases) tab.
- Launch MJUADS_Autosplitter_Utility.exe and follow instructions.

## Contributing
This software is made using wxWidgets 3.2.6. If you have any suggestions or want to notify me of bugs/problems, you can contact me on Discord (@skyywaffle).

# SingleInputCharacter
 A Unreal Engine Character desgined around using one input - only a mouse or a single finger

 <p align="center">
  <img src="https://github.com/profdambledore/SingleInputCharacter/blob/main/Images/v05-001.png" />
</p>

In this project, I am creating a complex character with all of the features required from a modern game ‑ such as inventory with sorting, combat, crafting, simple movement and more ‑ while dealing with the limitation of only having one input device of mouse and the left mouse button.

## Project Document
 
 [Coming Soon]()

  ## Latest Update
<table><tr><td valign="center" width="100%">
 
### v0.5 - Alphabetical Sorting

-- Assets --  
Added Synty PolygonApocalypse assets (gitignored)

-- SingleInputInventory --  
Updated InventoryOrder to use a property rather than the array length
 - I incorrectly stated that you could use a const to increment.  Instead, I am using a non const integar.     
 
Added more comments   
Added Newest and Oldest selections to SortInventory  
Implemented SortInventoryNewest and SortInventoryOldest
 - Basically do the same things, except Newest reverses it's output array before setting the inventory

-- SingleInputPerson --

Updated mesh position  
Added a character skeletal mesh from PolygonApocalypse

 -- InventoryUI --
 
Implemented ClearDescriptionBox, which resets the description box
 - This is done as when the TileView is sorted, every element is destroyed and recreated with ClearListView
 - Also sets CurrentSelectedItem to nullptr  

Added buttons to sort by Newest and Oldest (see Image/05-001.png)
</td></tr></tr></table> 

 ## Assets Used:
- PolygonApocalypse by SyntyStudios

## Programs Used:
- Unreal Engine 5.2 - Game Engine.
- Visual Studio 2022 - Code Editing.
- Overleaf with LaTeX - Document Creation
- GitHub Desktop - Git Control. 

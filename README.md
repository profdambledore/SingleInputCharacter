# SingleInputCharacter
 A Unreal Engine Character desgined around using one input - only a mouse or a single finger

 <p align="center">
  <img src="" />
</p>

In this project, I am creating a complex character with all of the features required from a modern game ‑ such as inventory with sorting, combat, crafting, simple movement and more ‑ while dealing with the limitation of only having one input device of mouse and the left mouse button.

## Project Document
 
 [Coming Soon]()

  ## Latest Update
<table><tr><td valign="center" width="100%">
 
### v0.4 - Alphabetical Sorting

 -- ItemData --
 
Added EInventorySortType, which is used to choose or store how the player's inventory should be sorted
Added InventoryOrder, used to store the order that this item was added to the inventory
Added a new constructor that allows an argument for InventoryOrder

 -- SingleInputInventory --
 
Updated AddItemToArray to use InventoryOrder
 - Currently uses the array length, should be updated to a const int that is incremented each time a new item is added
Added SortInventoryAlphabetically function
 - Goes through the array, using FString::Compare to sort alphabetically
Added SortInventory
 - Take in EInventorySortType to change how the inventory is sorted, then sorts
Added ReSortInventory function
 - Simply calls SortInventory with the InventorySort as the argument

 -- SingleInputPerson --
 
Modified the test values that are added to the array

 -- InventoryUI --
 
Added a button to sort the inventory, as well as a delegate bind to update the sorting type then call SyncronizeProperties
Updated SyncronizeProperties to call ReSortInventory when called
</td></tr></tr></table> 

 ## Assets Used:


## Programs Used:
- Unreal Engine 5.2 - Game Engine.
- Visual Studio 2022 - Code Editing.
- Overleaf with LaTeX - Document Creation
- GitHub Desktop - Git Control. 

# SingleInputCharacter
 A Unreal Engine Character desgined around using one input - only a mouse or a single finger

 <p align="center">
  <img src="https://github.com/profdambledore/SingleInputCharacter/blob/main/Images/v06-001.png" />
</p>

In this project, I am creating a complex character with all of the features required from a modern game ‑ such as inventory with sorting, combat, crafting, simple movement and more ‑ while dealing with the limitation of only having one input device of mouse and the left mouse button.

## Project Document
 
 [Coming Soon]()

  ## Latest Update
<table><tr><td valign="center" width="100%">
 
### v0.6 - Inventory Visuals and Slight Item Rework

-- Item Display --

Item Display is used to render a 3D model of the item when selected in the inventory
 - Later will also be used by crafting

Added Components
 - MeshDisplay_Static is used for Static meshes, while Skel is used for skeletal meshes
 - DisplaySpringArm has the DisplayCapture attached to it.
   
Implemented SetNewMeshTarget function
 - Displays the inputted static or skeletal mesh - if two meshes are somehow inputted only the static mesh will be shown
 - Also allows the spring arm length to be modified to the mesh
   
Also implemented the ClearMeshTarget function, which simply clears any meshes currently set.
Added CanvasRenderTarget CRT_ItemDisplay, used to show the output of the ItemDisplay
Added Material M_ItemDisplay, used to convert the output to a user interface material
 - Utilizes a OneMinus and a Multiply to remove the background of the capture
 - See Images/v06-002.png


 -- InventoryUI --
 
Added a pointer to the ItemDisplay spawned by the UI
 - Will be updated to be spawned by the SingleInputPerson, so multiple menus can use the ItemDisplay

Now calls SetNewMeshTarget when the description box is updated


 -- InventorySlot --
 
Added SelectItemImage Image component, used to display a Material Instance of the item's icon
 - See v06-001.png


 -- SingleInputPerson --
 
Updated how the test items are inputted into the inventory


 -- SingleInputInventory --
 
Reworked how items are added to the inventory
 - No longer takes in the FItemData, instead takes in an ItemID and an amount
 - Now has a pointer to the ItemDataTable
 - When a new item is added to the inventory the ID is queried in the data table, returning the matching row
 - The data from this row is added to the inventory, rather than the inputted struct
Implemented FindItemData function, used to search the data table asset.


 -- ItemData --
 
Added Item Display section
 - Static/SkeletalMesh properties are used for the item's mesh
 - Icon is used for the display picture in the UI
Updated constructors
 - Now only takes in a full struct alongside the amount and inventory order
Updated AddItems
 - Now only requires an ID alongside the amount to add, rather that a whole struct


 -- Prototyping --
 
Added BP prototype of ItemDisplay


 -- DT_ItemData --
 
Updated Data Table with static/skeletal meshes and icons


 -- WBP_InventorySlot --
 
Updated OnListItemObjectSet event to now set a new DynamicMaterialInstance of M_Icon_Ins on the SelectItemImage Image component, then update the IconTexture parameter with the icon from ItemData
 - See Images/06-003.png


-- WS_Inventory --
Updated the SelectedItemImage to now use the M_ItemDisplay material
 - Also see Images/v06-001.png


 -- IconCreation --
Added a EditorUtility object to create images of either static or skeletal meshes from the editor
 - When the Scripted Asset Action is called, it spawns a BP_IconCreation actor into the world, sets one of its mesh components (depending on if it is a static or skeletal mesh asset).
 - After a delay, the Render Target creates a static texture of the mesh spawned in the world
 - The IconCreation is then destroyed.
 - See Images/v06-004.png to Images/v06-007.png
 -- Modified from Aulden Carter's 'Generating Images From Meshes in UE5' (https://www.youtube.com/watch?v=_IHbHPnp_sc) to use both static and skeletal meshes


 -- Icons --
 
Added icons for the items used in the data table, created via the IconCreation tool
</td></tr></tr></table> 

 ## Assets Used:
- PolygonApocalypse by SyntyStudios

## Programs Used:
- Unreal Engine 5.2 - Game Engine.
- Visual Studio 2022 - Code Editing.
- Overleaf with LaTeX - Document Creation
- GitHub Desktop - Git Control. 

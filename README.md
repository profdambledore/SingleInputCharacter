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
 
### v0.7 - Items and AI
-- ParentItem --

Added superclass, used by all item types (weapon, armour, common)
Added virtual class SetupItem, which is to be overridden in the child classes
Added an AActor pointer to the item's owner
- This is so when it is equipped, if it has an owner the item cannot be accidentally clicked by the player, or they cannot start picking up an item in the enemies hands

Added FItemData struct, for holding the item data

-- CommonItem --

CommonItem is a subclass of ParentItem
Added a static mesh component, which is setup in the constructor
Overrides SetupItem, which simply sets the ItemData with the argument inputted then sets the static mesh with the one in the item

-- ItemData --

Added EContextStat, used by items to change what stat is associated with them (damage for weapons, defence for armour for example)
Added EContextStat StatType to FItemData;
Added int StatAmount to FItemData, used to display the amount of the context stat this item has
Added FString Desc, used to display a description of an item
Added TSubclassOf<AParentItem> Class, used to spawn a class of the item when needed
Added TArray of FStrings UpgradeTags, used to add upgrades to inventory items

-- SingleInputPlayerController --

Updated the location of the UI class

-- SingleInputAIController --

Added a BehaviorTreeComponent and a Blackboard component, used by the BehaviorTree to control the pawn
Added a pointer to the current BehaviorTree
Added OnPossess which overrides from AIController
- Called when this controller possesses a new pawn
- On possession, Initialize the set blackboard, update the Blackboard value of "SelfActor" with the new pawn and start the tree.

Implemented function MoveState, which updates the Blackboard values to change the AI to their MoveState
Implemented function PickupItemState, which updates the Blackboard values to change the AI to their PickupItemState

-- SingleInputPerson --

Removed test items added on BeginPlay
Updated MoveToLocation with the new AI functions

-- SingleInputInventory --

Made AddItemToArray callable in BluePrints

-- Prototype --

Prototyped how the AI for the person would work with PROTO_AICont, PROTO_BT and PROTO_TaskMoveLoc

-- AI --

Added BT_Player and BB_Player assets
- Currently, BT_Player has two paths, a Move path and a Pickup path chosen based on the current AI state
- In state Move, the AI simply moves to the set TargetLocation. Once they reach their destination the state is cleared
- In state Pickup, the AI moves to the item, then collects the item. Again after the item is collected the state is cleared
- The Blackboard has 4 keys, with each being sorted based on which state uses them
- See Images/v07-001.png and Images/v07-002.png
  
Added Decorator tasks, but they will be removed as they are not used
- Now using the Blackboard decorator types, as they can query strings
  
Added BTTask_ClearState, which simply sets the inputted string key to "" when called
- See Images/v07-003.png
  
Added BTTask_CollectPickup, which adds the item to the AI pawn's inventory and calls pickup on the item
- See Images/v07-004.png

-- Inputs --

Updated IMC_SingleInput to now use a Pulse type instead of Hold type
- Hold fires each frame after a duration, while Pulse has a delay between inputs

-- Structure --

Updated BP folder structure to better resemble the one featured in https://github.com/Allar/ue5-style-guide


</td></tr></tr></table> 

 ## Assets Used:
- PolygonApocalypse by SyntyStudios

## Programs Used:
- Unreal Engine 5.2 - Game Engine.
- Visual Studio 2022 - Code Editing.
- Overleaf with LaTeX - Document Creation
- GitHub Desktop - Git Control. 

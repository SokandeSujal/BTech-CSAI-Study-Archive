# Assignment 4 AVL Tree - Complete Explanation

This document explains `Assignment_4_AVL_Tree.cpp` line by line and includes a sample dry run.

## 1) Line-by-Line Explanation

### Lines 1-4: Headers and namespace

- **Line 1**: `#include <iostream>` imports input/output (`cin`, `cout`).
- **Line 2**: `#include <algorithm>` imports `max()` used for height updates.
- **Line 3**: `using namespace std;` avoids writing `std::` repeatedly.
- **Line 4**: Blank line for readability.

### Lines 5-22: Class and Node definition

- **Line 5**: Starts class `AVLTree`.
- **Line 6**: `private:` section begins.
- **Line 7**: Starts inner `Node` structure.
- **Line 8**: `data` stores key value of the node.
- **Line 9**: `height` stores subtree height rooted at this node.
- **Line 10**: `left` pointer to left child.
- **Line 11**: `right` pointer to right child.
- **Line 12**: Blank line.
- **Line 13**: Node constructor starts.
- **Line 14**: Stores constructor value into `data`.
- **Line 15**: Sets initial node height to `1` (leaf height).
- **Line 16**: Initializes left child pointer to `NULL`.
- **Line 17**: Initializes right child pointer to `NULL`.
- **Line 18**: Ends constructor.
- **Line 19**: Ends `Node` struct.
- **Line 20**: Blank line.
- **Line 21**: `root` pointer stores top node of AVL tree.
- **Line 22**: Blank line.

### Lines 23-28: `getHeight`

- **Line 23**: Function `getHeight(Node* node)` starts.
- **Line 24**: Checks if node is `NULL`.
- **Line 25**: Returns `0` for empty subtree.
- **Line 26**: Ends `if`.
- **Line 27**: Returns stored height for non-null node.
- **Line 28**: Ends function.

### Lines 30-35: `getBalance`

- **Line 30**: Function `getBalance(Node* node)` starts.
- **Line 31**: If node is `NULL`.
- **Line 32**: Balance is `0` for null node.
- **Line 33**: Ends `if`.
- **Line 34**: Returns balance factor = left height - right height.
- **Line 35**: Ends function.

### Lines 37-48: `rightRotate`

- **Line 37**: Starts right rotation function.
- **Line 38**: `x` is left child of `y` (will become new root of rotated subtree).
- **Line 39**: `t2` stores right subtree of `x` temporarily.
- **Line 40**: Blank line.
- **Line 41**: Makes `y` right child of `x`.
- **Line 42**: Connects `t2` as left child of `y`.
- **Line 43**: Blank line.
- **Line 44**: Recalculates height of old root `y`.
- **Line 45**: Recalculates height of new root `x`.
- **Line 46**: Blank line.
- **Line 47**: Returns new subtree root `x`.
- **Line 48**: Ends function.

### Lines 50-61: `leftRotate`

- **Line 50**: Starts left rotation function.
- **Line 51**: `y` is right child of `x` (new root after rotation).
- **Line 52**: `t2` stores left subtree of `y` temporarily.
- **Line 53**: Blank line.
- **Line 54**: Makes `x` left child of `y`.
- **Line 55**: Connects `t2` as right child of `x`.
- **Line 56**: Blank line.
- **Line 57**: Updates height of old root `x`.
- **Line 58**: Updates height of new root `y`.
- **Line 59**: Blank line.
- **Line 60**: Returns new subtree root `y`.
- **Line 61**: Ends function.

### Lines 63-102: `insertNode`

- **Line 63**: Starts recursive insertion function.
- **Line 64**: If current position is empty.
- **Line 65**: Creates new node with key and returns it.
- **Line 66**: Ends `if`.
- **Line 67**: Blank line.
- **Line 68**: If key is smaller than current node value.
- **Line 69**: Recur left and attach returned subtree.
- **Line 70**: Ends first branch.
- **Line 71**: If key is larger than current node value.
- **Line 72**: Recur right and attach returned subtree.
- **Line 73**: Ends second branch.
- **Line 74**: Handles equal key (duplicate).
- **Line 75**: Prints duplicate-not-allowed message.
- **Line 76**: Returns unchanged node (no insertion).
- **Line 77**: Ends duplicate branch.
- **Line 78**: Blank line.
- **Line 79**: Updates current node height after insertion.
- **Line 80**: Blank line.
- **Line 81**: Computes current balance factor.
- **Line 82**: Blank line.
- **Line 83**: Checks LL case (`balance > 1` and key went to left of left child).
- **Line 84**: Fixes LL using right rotation.
- **Line 85**: Ends LL case.
- **Line 86**: Blank line.
- **Line 87**: Checks RR case (`balance < -1` and key went to right of right child).
- **Line 88**: Fixes RR using left rotation.
- **Line 89**: Ends RR case.
- **Line 90**: Blank line.
- **Line 91**: Checks LR case (`balance > 1` and key in left child's right subtree).
- **Line 92**: First rotate left at left child.
- **Line 93**: Then rotate right at current node.
- **Line 94**: Ends LR case.
- **Line 95**: Blank line.
- **Line 96**: Checks RL case (`balance < -1` and key in right child's left subtree).
- **Line 97**: First rotate right at right child.
- **Line 98**: Then rotate left at current node.
- **Line 99**: Ends RL case.
- **Line 100**: Blank line.
- **Line 101**: If no imbalance, return current node.
- **Line 102**: Ends function.

### Lines 104-118: `searchNode`

- **Line 104**: Starts recursive BST search.
- **Line 105**: If node is `NULL`.
- **Line 106**: Key not found in this path.
- **Line 107**: Ends `if`.
- **Line 108**: Blank line.
- **Line 109**: If current node contains key.
- **Line 110**: Returns found = `true`.
- **Line 111**: Ends check.
- **Line 112**: Blank line.
- **Line 113**: If key is smaller than current value.
- **Line 114**: Search continues in left subtree.
- **Line 115**: Ends `if`.
- **Line 116**: Blank line.
- **Line 117**: Otherwise search right subtree.
- **Line 118**: Ends function.

### Lines 120-126: `inorderNode`

- **Line 120**: Starts recursive inorder traversal.
- **Line 121**: Traverses only if node exists.
- **Line 122**: Visit left subtree first.
- **Line 123**: Print current node.
- **Line 124**: Visit right subtree.
- **Line 125**: Ends `if`.
- **Line 126**: Ends function.

### Lines 128-134: `preorderNode`

- **Line 128**: Starts recursive preorder traversal.
- **Line 129**: Traverses only if node exists.
- **Line 130**: Print current node first.
- **Line 131**: Visit left subtree.
- **Line 132**: Visit right subtree.
- **Line 133**: Ends `if`.
- **Line 134**: Ends function.

### Lines 136-142: `postorderNode`

- **Line 136**: Starts recursive postorder traversal.
- **Line 137**: Traverses only if node exists.
- **Line 138**: Visit left subtree first.
- **Line 139**: Visit right subtree.
- **Line 140**: Print current node last.
- **Line 141**: Ends `if`.
- **Line 142**: Ends function.

### Lines 144-149: `countNodes`

- **Line 144**: Starts recursive node counting.
- **Line 145**: If subtree empty.
- **Line 146**: Count is `0`.
- **Line 147**: Ends `if`.
- **Line 148**: Returns `1 + left count + right count`.
- **Line 149**: Ends function.

### Lines 151-157: `clearTree`

- **Line 151**: Starts postorder deletion function.
- **Line 152**: Process only non-null node.
- **Line 153**: Delete left subtree first.
- **Line 154**: Delete right subtree.
- **Line 155**: Delete current node.
- **Line 156**: Ends `if`.
- **Line 157**: Ends function.

### Lines 159-166: Public constructor and destructor

- **Line 159**: `public:` section begins.
- **Line 160**: Constructor `AVLTree()` starts.
- **Line 161**: Initializes `root` to `NULL` (empty tree).
- **Line 162**: Ends constructor.
- **Line 163**: Blank line.
- **Line 164**: Destructor `~AVLTree()` starts.
- **Line 165**: Calls `clearTree(root)` to free memory.
- **Line 166**: Ends destructor.

### Lines 168-170: Public `insert`

- **Line 168**: Public insert wrapper starts.
- **Line 169**: Updates root with recursive insertion result.
- **Line 170**: Ends function.

### Lines 172-179: Public `search`

- **Line 172**: Public search wrapper starts.
- **Line 173**: Calls recursive search from root.
- **Line 174**: If found, prints success message.
- **Line 175**: Ends `if` body.
- **Line 176**: Otherwise branch.
- **Line 177**: Prints not-found message.
- **Line 178**: Ends `else`.
- **Line 179**: Ends function.

### Lines 181-185: Public `inorder`

- **Line 181**: Inorder display wrapper starts.
- **Line 182**: Prints label `Inorder:`.
- **Line 183**: Calls recursive inorder traversal.
- **Line 184**: Prints newline after traversal output.
- **Line 185**: Ends function.

### Lines 187-191: Public `preorder`

- **Line 187**: Preorder display wrapper starts.
- **Line 188**: Prints label `Preorder:`.
- **Line 189**: Calls recursive preorder traversal.
- **Line 190**: Prints newline.
- **Line 191**: Ends function.

### Lines 193-197: Public `postorder`

- **Line 193**: Postorder display wrapper starts.
- **Line 194**: Prints label `Postorder:`.
- **Line 195**: Calls recursive postorder traversal.
- **Line 196**: Prints newline.
- **Line 197**: Ends function.

### Lines 199-203: `displayAllTraversals`

- **Line 199**: Starts helper to print all traversals.
- **Line 200**: Calls inorder.
- **Line 201**: Calls preorder.
- **Line 202**: Calls postorder.
- **Line 203**: Ends function.

### Lines 205-208: `showTreeInfo`

- **Line 205**: Starts tree info display function.
- **Line 206**: Prints total node count.
- **Line 207**: Prints tree height.
- **Line 208**: Ends function.

### Lines 209-262: `main` menu-driven program

- **Line 209**: Ends class `AVLTree`.
- **Line 210**: Blank line.
- **Line 211**: Starts `main()` function.
- **Line 212**: Creates AVL tree object.
- **Line 213**: Declares menu choice and input value variables.
- **Line 214**: Blank line.
- **Line 215**: Starts `do` loop for repeated menu interaction.
- **Line 216**: Prints menu options.
- **Line 217**: Prompts for choice.
- **Line 218**: Reads choice.
- **Line 219**: Blank line.
- **Line 220**: Starts `switch(choice)`.
- **Line 221**: Case 1 = Insert.
- **Line 222**: Prompts for value to insert.
- **Line 223**: Reads value.
- **Line 224**: Calls `tree.insert(value)`.
- **Line 225**: Ends case 1.
- **Line 226**: Blank line.
- **Line 227**: Case 2 = Search.
- **Line 228**: Prompts for value to search.
- **Line 229**: Reads value.
- **Line 230**: Calls `tree.search(value)`.
- **Line 231**: Ends case 2.
- **Line 232**: Blank line.
- **Line 233**: Case 3 = Inorder display.
- **Line 234**: Calls `tree.inorder()`.
- **Line 235**: Ends case 3.
- **Line 236**: Blank line.
- **Line 237**: Case 4 = Preorder display.
- **Line 238**: Calls `tree.preorder()`.
- **Line 239**: Ends case 4.
- **Line 240**: Blank line.
- **Line 241**: Case 5 = Postorder display.
- **Line 242**: Calls `tree.postorder()`.
- **Line 243**: Ends case 5.
- **Line 244**: Blank line.
- **Line 245**: Case 6 = Display all traversals.
- **Line 246**: Calls `tree.displayAllTraversals()`.
- **Line 247**: Ends case 6.
- **Line 248**: Blank line.
- **Line 249**: Case 7 = Tree info.
- **Line 250**: Calls `tree.showTreeInfo()`.
- **Line 251**: Ends case 7.
- **Line 252**: Blank line.
- **Line 253**: Case 8 = Exit option.
- **Line 254**: Breaks from switch.
- **Line 255**: Blank line.
- **Line 256**: Default case for invalid choice.
- **Line 257**: Prints invalid choice message.
- **Line 258**: Ends switch.
- **Line 259**: Ends loop when choice is 8.
- **Line 260**: Blank line.
- **Line 261**: Returns success status from `main`.
- **Line 262**: Ends `main`.

## 2) Function-Wise Summary

- `getHeight(node)`: Returns height, or `0` if node is null.
- `getBalance(node)`: Returns AVL balance factor (`leftHeight - rightHeight`).
- `rightRotate(y)`: Fixes left-heavy subtree (LL side).
- `leftRotate(x)`: Fixes right-heavy subtree (RR side).
- `insertNode(node, key)`: BST insertion + AVL balancing (LL, RR, LR, RL).
- `searchNode(node, key)`: BST-style recursive search.
- `inorderNode`, `preorderNode`, `postorderNode`: Recursive traversals.
- `countNodes(node)`: Counts all nodes in subtree.
- `clearTree(node)`: Frees memory using postorder deletion.
- Public wrappers (`insert`, `search`, traversal displays): user-facing calls.
- `showTreeInfo()`: Prints total nodes and current height.
- `main()`: Menu-driven interface for repeated operations.

## 3) Sample Dry Run

Use this insertion sequence: **30, 20, 10, 25, 40, 50**

### Step 1: Insert 30

- Tree: `30`
- Height(30) = 1, balanced.

### Step 2: Insert 20

- 20 < 30, goes left.
- Tree:

```text
   30
  /
20
```

- Balance at 30 = `1`, still balanced.

### Step 3: Insert 10

- 10 < 30, go left; 10 < 20, go left.
- Before balancing:

```text
    30
   /
  20
 /
10
```

- Balance at 30 becomes `+2` and key inserted in left-left path => **LL case**.
- Perform `rightRotate(30)`.
- After rotation:

```text
   20
  /  \
10   30
```

### Step 4: Insert 25

- 25 > 20, go right to 30; 25 < 30, go left.
- Tree:

```text
    20
   /  \
 10   30
      /
     25
```

- All balances remain within `[-1, 1]`.

### Step 5: Insert 40

- 40 > 20 -> right to 30 -> right of 30.
- Tree:

```text
    20
   /  \
 10   30
      / \
     25 40
```

- Still balanced.

### Step 6: Insert 50

- 50 > 20 -> 30 -> 40 -> right.
- Before balancing:

```text
    20
   /  \
 10   30
      / \
     25 40
          \
          50
```

- Balance at 20 becomes `-2` and key inserted in right-right path => **RR case**.
- Perform `leftRotate(20)`.
- Final AVL tree:

```text
      30
     /  \
   20    40
  / \     \
10  25    50
```

### Traversal outputs on final tree

- Inorder (LNR): `10 20 25 30 40 50`
- Preorder (NLR): `30 20 10 25 40 50`
- Postorder (LRN): `10 25 20 50 40 30`

### Search dry run examples

- Search `25`:
  - Compare with 30 -> smaller, go left.
  - Compare with 20 -> greater, go right.
  - Compare with 25 -> found.

- Search `35`:
  - Compare with 30 -> greater, go right.
  - Compare with 40 -> smaller, go left.
  - Left is null -> not found.


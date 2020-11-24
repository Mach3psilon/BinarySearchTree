# -*- coding: utf-8 -*-
"""
Created on Wed Nov  4 11:00:33 2020

@author: Eray Okutay
"""

import time

#https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/ (I've took the recursion idea)
#Appends elements to preorderTree in preorder sequence with recursion
def printInorder(BinarySearchTree,root,preorderTree): 
    
    if root!=0: 
  
        #Recursion of left child 
        element_index = findElementIndex(BinarySearchTree, root)
        
        printInorder(BinarySearchTree,BinarySearchTree[element_index][0],preorderTree) 
  
        #append root        
        preorderTree.append(BinarySearchTree[element_index][1])
        
        #Recursion of right child 
        printInorder(BinarySearchTree,BinarySearchTree[element_index][2],preorderTree)  






#initializes the tree with root
def setRoot(BinarySearchTree,root):
    BinarySearchTree.append([0,root,0,0])
    
 
#finds the index of element in tree
def findElementIndex(BinarySearchTree, element):
    for i in range(len(BinarySearchTree)):
        if BinarySearchTree[i][1] == element:
            return i
#returns 1 if element's left is empty           
def isLeftEmpty(BinarySearchTree, element_index):
    if not BinarySearchTree:
        print("Tree is Empty")
        return 0
    else:
        
        if BinarySearchTree[element_index][0] == 0:
            return 1
        else: 
            return 0
        
#returns 1 if element's right is empty              
def isRightEmpty(BinarySearchTree, element_index):
    if not BinarySearchTree:
        print("Tree is Empty")
        return 0
    
    else:
        
        if BinarySearchTree[element_index][2] == 0:
            return 1
        else: 
            return 0

#Sets the left child of the element in the given index
def setLeft(BinarySearchTree, element_index, child) :
    if not BinarySearchTree:
        print("Tree is Empty")
        return 0
    else:
        
            BinarySearchTree[element_index][0]  = child
            BinarySearchTree.append([0,child,0,BinarySearchTree[element_index][3]+1])
        
#Sets the right child of the element in the given index        
def setRight(BinarySearchTree, element_index, child) :
    if not BinarySearchTree:
        print("Tree is Empty")
        return 0
    else:
        BinarySearchTree[element_index][2]  = child
        BinarySearchTree.append([0,child,0,BinarySearchTree[element_index][3]+1])

#Integrates the functions and build the tree in format of {{leftChild,rootValue,rightChild},...} with recursion
def putItCorrect(BinarySearchTree, element_index, child):
    if BinarySearchTree[element_index][1] > child:
       
        if isLeftEmpty(BinarySearchTree, element_index) == 1:
           setLeft(BinarySearchTree, element_index, child)
        else:
            putItCorrect(BinarySearchTree, findElementIndex(BinarySearchTree, BinarySearchTree[element_index][0]), child) 
   
    elif BinarySearchTree[element_index][1] < child: 
      
        if isRightEmpty(BinarySearchTree, element_index) == 1:
            setRight(BinarySearchTree, element_index, child)
        else:
            putItCorrect(BinarySearchTree, findElementIndex(BinarySearchTree, BinarySearchTree[element_index][2]), child)
   






#Beautifies the Tree to correct form
#I no longer use this function
def beautify(BinarySearchTree):
    coolTree = []
    
    coolestRootIndex = 0
    for i in range(len(BinarySearchTree)):
        if coolestRootIndex <= BinarySearchTree[i][3]:
            coolestRootIndex = BinarySearchTree[i][3]
    for i in range(coolestRootIndex+1):
        coolTreeModule = []
        for b in range(len(BinarySearchTree)) :
            if BinarySearchTree[b][3] == i:
                coolTreeModule.append(BinarySearchTree[b][1])
                coolTreeModule.sort()
        coolTree.append(coolTreeModule)
    
    return coolTree
            
#Integrates the functions and build the tree in format of {{leftChild,rootValue,rightChild},...} with recursion 
def process_a_list(numberList,file):
    start = time.process_time()
    preorderTree = []
    root = numberList[0]
    BinarySearchTree = []
    setRoot(BinarySearchTree,root)
    
    for i in range(1,len(numberList)):
        element_index = 0
        child = numberList[i]
        putItCorrect(BinarySearchTree, element_index, child)   
    printInorder(BinarySearchTree,root,preorderTree)#here
    print(preorderTree)
#    coolTree = beautify(BinarySearchTree)
    print("\nBuilding the tree took",start, "seconds:\n")
    time_str = "\nBuilding the tree below took "+str(start)+" seconds:\n"
    file.write(time_str)
    treeToString = str(preorderTree) +"\n"
    file.write(treeToString)
  #  for i in coolTree:
  #      print(i)    
  #      str_data = str(i) + "\n"
   # file.write(str_data)
    file.write("------------------------------------------------------------\n")
    
        
        



def main():
    
    f = open("data.txt", "r")
    file = open("treeData.txt", "a")
    file.truncate(0)
    for i in f.readlines():
       # print(i)
        numberList = []
        
        line = i
        lines = line.split(" ")
        for b in lines:
            numberList.append(int(b))
   #     print(numberList)
        
        process_a_list(numberList,file)
    
    f.close()
    file.close()   

main()















                
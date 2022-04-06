import re
import string


def ItemCounter(v): #function to count the frequency of each item in a file

    file = open("GroceriesPurchased.txt", 'r') #open file to read
    f = file.readlines() #read the lines of the file

    fileList = [] #make list to file with contents of the file

    for line in f:
        fileList.append(line.strip()) #add contents from the file to the list while removing new line
    
    itemCount = dict((i, fileList.count(i)) for i in fileList) #make dictonary of list elements with the item as the key and frequency as the values
    
    for i in itemCount:
        print(i, itemCount[i])  #iterate through the dictionary and output the keys with thier values

    file.close() #close file when finished



def ItemFrequency(v): #function to output the frequency of a sinlge item in a file 
    
    file = open("GroceriesPurchased.txt", 'r')
    f = file.readlines()

    fileList = []

    for line in f:
        fileList.append(line.strip())
    
    itemFrequency = dict((v, fileList.count(v)) for i in fileList)
    
    for i in itemCount:
        print(i, itemFrequency[i]) #outputs the item and its frequency from a dictionary
    
    file.close()
    return 0; #returns 0 to run in c++ code

def HistogramFile(): #function to create new file from the contents of another file
    file = open("GroceriesPurchased.txt", 'r') #open and read existing file 
    f = file.readlines()

    fileList = []

    for line in f:
        fileList.append(line.strip()) #extracting data from existing file
    
    itemCount = dict((i, fileList.count(i)) for i in fileList)
    
    newFile = open("frequency.dat", 'a') #creating a new file to append data too

    for i in itemCount:
        newFile.write(i + itemCount[i] * "*" + "\n") #appending data to new file

    newFile.close()
    file.close() #close files when finished

    


    





    

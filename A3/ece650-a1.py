#!/usr/bin/env python3
import sys
import re

# YOUR CODE GOES HERE


#imported sys and re libraries to perform operations

#Function to find the boundaries of the graph

def find_graph_boundaries(vertex):
    if not vertex:
        return None
    x_min = float('inf')
    x_max = float('-inf')
    y_min = float('inf')
    y_max = float('-inf')

    for x, y in vertex:
        x_min = float(min(x_min,x))
        y_min = float(min(y_min,y))
        x_max = float(max(x_max,x))
        y_max = float(max(y_max,y))

    return x_min,x_max,y_min,y_max

#Function to find the range of intersection points

def within_range(point,x_min,x_max,y_min,y_max):
    x, y = point
    return x_min <= x <= x_max and y_min <= y <= y_max

#Function to find new edges once an occurence of intersection is encountered

def newedges(vertex,segment1,segment2,intersections,edges):
    vertex2 = []
    vertex2 = vertex + intersections
    vertex3 = []
    for vertices in vertex2:
        if vertices not in vertex3:
            vertex3.append(vertices)
    
    vertex = vertex3
    seg1 = []
    seg2 = []
    dup = []
    dup.append((intersections[0],intersections[0]))
    seg1 = segment1
    seg2 = segment2
    for r in edges[:]:
        if seg1 == r:
            edges.remove(r)
        elif seg2 == r:
            edges.remove(r)
    newe = []
    newe1 = []
    newe.append(seg1[0])
    newe.append(seg1[1])
    newe.append(seg2[0])
    newe.append(seg2[1])
    newe1.append(intersections[0])
    for t in range(len(newe)):
        edges.append((newe[t],newe1[0]))
    for x in range(len(edges)):
        if((edges[x]) == dup[0]):
            edges.remove(edges[x])
            break
    

    return vertex, edges

#Function to find the intersection of two lines

def intersect1(names,vertex,edges,intersections,temp):
    abc = 1
    f = 1
    frun = 1
    while(abc):
        abc = 0
        efg = 0
        gif = 0
        intersections1 = []
        for i in range(len(edges)):
            gif = 1
            while(gif == 1):
                gif = 0
                for j in range(i+1, len(edges)):
                    segment1 = edges[i]
                    segment2 = edges[j]
                    c = 0
                    if ((segment1[0] == segment2[0]) or (segment1[0] == segment2[1]) or (segment1[1] == segment2[0]) or (segment1[1] == segment2[1])):
                        c = c+1
                    if(c == 0):

                        dir_vector1 = (segment1[1][0]-segment1[0][0], segment1[1][1]-segment1[0][1])
                        dir_vector2 = (segment2[1][0]-segment2[0][0], segment2[1][1]-segment2[0][1])

                        det = dir_vector1[0] * dir_vector2[1] - dir_vector1[1] * dir_vector2[0]

                        if det == 0:
                            pass
                        else:

                            difference = (segment2[0][0]-segment1[0][0], segment2[0][1]-segment1[0][1])
                            t1 = (difference[0] * dir_vector2[1] - difference[1] * dir_vector2[0])/det
                            t2 = (difference[0] * dir_vector1[1] - difference[1] * dir_vector1[0])/det

                            x = segment1[0][0] + t1 * dir_vector1[0]
                            y = segment1[0][1] + t1 * dir_vector1[1]

                            intersections.append((x,y))
                    intersections1 = list(intersections)
                #if i == len(edges)-2:
                 #   efg = 1
                    while (len(intersections) != 0):
                        x_min,x_max,y_min,y_max = find_graph_boundaries(vertex)
                        index = 0

                        for segment in intersections1:
                            if within_range(segment,x_min,x_max,y_min,y_max):
                                if ((((segment1[0][0]) <= intersections[0][0] <= (segment1[1][0])) or ((segment1[1][0]) <= intersections[0][0] <= (segment1[0][0]))) and (((segment2[0][0]) <= intersections[0][0] <= (segment2[1][0])) or ((segment2[1][0]) <= intersections[0][0] <= (segment2[0][0])))) and (((segment1[0][1]) <= intersections[0][1] <= (segment1[1][1])) or ((segment1[1][1]) <= intersections[0][1] <= (segment1[0][1]))) and (((segment2[0][1]) <= intersections[0][1] <= (segment2[1][1])) or ((segment2[1][1]) <= intersections[0][1] <= (segment2[0][1]))):
                                    vertex,edges = newedges(vertex,segment1,segment2,intersections,edges)
                                    temp.append(intersections)
                                    intersections = []
                                    gif = 1
                                    break

                        else:
                                index = intersections.index(segment)
                                intersections.pop(index)
                                break
                    if gif == 1:
                        break
        if(frun != 0):
            frun = 0
            abc = 1
            continue
        elif i == len(edges) -1:
            break
    vertedgerearr(vertex,edges,temp)

#Function to print the vertex and edges list obtained by finding intersection of coordinates generated from random generator program.
 
def printoutput(vertex,edges):
    v = vertex
    e = edges
    arr = 0
    for c in range(len(v)):
        arr = arr + 1
    print(f"V {arr}", flush=True)

    indices = []
    for q in e:
        index_pair = []
        for r in q:
            if r in v:
                index = v.index(r)
                index_pair.append(index)
        if len(index_pair) == 2:
            indices.append(index_pair)
    out = "{" + ",".join([f"<{x[0]+1},{x[1]+1}>" for x in indices]) + "}"
    print(f"E {out}",flush=True)




#Function to rearrange the vertex and edges based on intersection conditions

def vertedgerearr(vertex,edges,temp):
    #temp = temp + temp1
    temp2 = []
    for t in temp:
        if t not in temp2:
            temp2.append(t)
    
    temp = temp2
    rr1 = []
    rr2 = []
    f = 1
    while(f == 1):
        keys1 = list(names.keys())
        for ab in range(len(keys1)-1):
            for bc in names[keys1[ab]]:
                for cd in range(ab+1,len(keys1)):
                    key_2 = keys1[cd]
                    for de in names[key_2]:
                        if bc == de:
                            rr1 = list(bc)
                            rr2 = [(x,y) for x, y in zip(rr1[::2], rr1[1::2])]
                            temp.append(rr2)
        f = 0
    g = 0
    edges2 = []
    m=0
    n=0

    for m in range(len(edges)):
        for n in range(len(temp)):
            var1 = edges[m]
            var2 = var1[0]
            var3 = var1[1]
            if(((var2[0] <= temp[n][0][0] <= var3[0]) or (var3[0] <= temp[n][0][0] <= var2[0])) and ((var2[1] <= temp[n][0][1] <= var3[1]) or (var3[1] <= temp[n][0][1] <= var2[1]))):
                break
            else:
                g+=1
        if(g <=n):
            edges2.append(edges[m])
        g = 0
    if temp != []:
        edges = edges2
    else:
        edges = []

    h = 0
    vertextemp = []
    for o in range(len(vertex)):
        for p in range(len(edges)):
            ch1 = edges[p]
            ch2 = ch1[0]
            ch3 = ch1[1]
            if((vertex[o] == ch2) or (vertex[o] == ch3)):
                break
            else:
                h+=1
        if(h != len(edges)):
            vertextemp.append(vertex[o])
        h = 0
    vertex = vertextemp

    printoutput(vertex,edges)

        
#Function to add a new street into a dictionary
        
def addstreet(names, street, coor):
    if street not in names:
        names[street] = []
    names[street].extend(coor)

#Function to add edges and vertices from dictionary

def addedge(names,vertex,edges):
    vertex = []
    edges = []
    street = ''
    a = names
    for key, value in a.items():
        vertex.extend(value)

    for street, coor in a.items():
        for i in range(len(coor)-1):
            edges.append((coor[i], coor[i+1]))
    temp = []
    intersections = []

    intersect1(names,vertex,edges,intersections,temp)

#Function to modify street data and append the dictionary
def modifystreet(names,street,coor):
    names[street] = coor

#Function to delete a street and make changes in the dictionary

def deletestreet(names,street,coor):
    del names[street]

#Function to parse the inputs and check for validations

def parseLine(line):
    temp1 = line.strip()
    par = re.split("\"", temp1)
    cmd = par[0].strip()
    if line == "add\n" or line == "mod\n" or line == "rm\n":
        raise Exception("Street name and coordinates are not given")
    if cmd != "add" and cmd!="mod" and cmd != "rm" and cmd!= "gg":
        raise Exception("Invalid input command")
    
    if cmd == "add":
        street = par[1]
        temp1 = temp1.replace(" ","")
        temp2 = par[2].replace(" ","")
        if temp2[0] != "(" or temp2[-1] != ")":
            raise Exception("Parantheses are not balanced")
        coor = re.findall(r'\(-?\d+,-?\d+\)', temp2)
        coor = [tuple(map(int, re.findall(r'-?\d+', c))) for c in coor]
        stack = []
        for o in range(len(temp2)):
            if temp2[o] == "(":
                stack.append(temp2[o])
            elif temp2[o] == ",":
                if stack[-1] == "(":
                    stack.append(temp2[o])
                else:
                    raise Exception("It is not of the expected format")

            elif temp2[o] == ")":
                if (stack[-1] == "," and stack[-2] == "("):
                    stack.pop()
                    stack.pop()
                else:
                    raise Exception("It is not of the expected format")
                
        pp = False
        for i in temp2:
            if i.isalpha():
                pp = True
        if pp:
            raise Exception("Alphabets should not be present in coordinates")
        ac = re.findall("\d+\.\d+",par[2])
        if ac != []:
           raise Exception("Decimal values not allowed in coordinates")
        if street == '':
            raise Exception("Street name is missing")
        if coor == []:
            raise Exception("Coordinates are missing")
        if len(coor) <= 1:
            raise Exception("Atleast two coordinates should be given")
        #ad = bool(re.findall(r'[ ]+', line))
        if par[0][-1] != " ":
            raise Exception("There is no spacing between command given")
        c = 0
        for y in names.keys():
            if street in y:
                c = 1
                break
        if (c == 1):
            raise Exception("The street to be added is already present")
            
    if cmd == "mod":
        street = par[1]
        coor = re.findall(r'\(-?\d+,-?\d+\)', temp1)
        coor = [tuple(map(int, re.findall(r'-?\d+', c))) for c in coor]
        temp1 = temp1.replace(" ","")
        temp2 = par[2].replace(" ","")
        if temp2[0] != "(" or temp2[-1] != ")":
            raise Exception("Parantheses are not balanced")
        stack = []
        for o in range(len(temp2)):
            if temp2[o] == "(":
                stack.append(temp2[o])
            elif temp2[o] == ",":
                if stack[-1] == "(":
                    stack.append(temp2[o])
                else:
                    raise Exception("It is not of the expected format")

            elif temp2[o] == ")":
                if (stack[-1] == "," and stack[-2] == "("):
                    stack.pop()
                    stack.pop()
                else:
                    raise Exception("It is not of the expected format")
        pp = False
        for i in temp2:
            if i.isalpha():
                pp = True
        if pp:
            raise Exception("Alphabets should not be present in coordinates")
        if street == '':
            raise Exception("Street to be modified should be given")
        if len(coor) < 2:
            raise Exception("Atleast two coordinates should be given")
        if par[0][-1] != " ":
            raise Exception("There is no spacing between command given")

        if names == {}:
            raise Exception("Atleast one street should be present to modfiy")
        d = 0
        for x in names.keys():
            if street in x:
                d = 1
        if(d != 1):
            raise Exception("The street to be modified is not present")
            
    if cmd == "rm":
        street = par[1]
        coor = re.findall(r'\(-?\d+,-?\d+\)', temp1)
        coor = [tuple(map(int, re.findall(r'-?\d+', c))) for c in coor]
        if street == '':
            raise Exception("Street to be removed should be given")
        if len(coor) != 0:
            raise Exception("Coordinates should not be given for removing street")
        if par[0][-1] != " ":
            raise Exception("There is no spacing between command given")

        if names == {}:
            raise Exception("Atleast one street should be present to remove")
        e = 0
        for z in names.keys():
            if street in z:
                e = 1
        if(e !=1):
            raise Exception("The street to be removed is not present")
        
        
    if cmd == "gg":
        street = ''
        coor = ''
        
    return cmd, street, coor

def main():
    # YOUR MAIN CODE GOES HERE
    global vertex, edge, intersections , names, temp, outputprint, elementcount
    vertex = []
    edge = []
    intersections = []
    newedge = []
    temp = []
    elementcount = {}
    names = {}
    outputprint = {}
    while True:
        line = sys.stdin.readline()
        if line == '':
            break
        #print("read a line:", line)
        try:
            cmd, street, coor = parseLine(line)
            if cmd == 'add':
                addstreet(names, street, coor)
            elif cmd == "mod":
                modifystreet(names,street,coor)
            elif cmd == "rm":
                deletestreet(names,street,coor)
            elif cmd == "gg":
                addedge(names,vertex,edge)
        except Exception as e:
            #print(line, file=sys.stderr)
            print('Error: ' + str(e), file=sys.stderr)
    sys.exit(0)


if __name__ == "__main__":
    main()

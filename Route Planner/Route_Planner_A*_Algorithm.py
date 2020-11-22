import math

def shortest_path(M,start,goal):
    
    frontier=set()
    explored=set()
    path=[]
    g_dict={
        "1":0,
        "2":0,
        "3":0,
        "4":0,
        "5":0,
        "6":0,
        "7":0,
        "8":0,
        "9":0,
        "10":0,
        "11":0,
        "12":0,
        "13":0,
        "14":0,
        "15":0,
        "16":0,
        "17":0,
        "18":0,
        "19":0,
        "20":0,
        "21":0,
        "22":0,
        "23":0,
        "24":0,
        "25":0,
        "26":0,
        "27":0,
        "28":0,
        "29":0,
        "30":0,
        "31":0,
        "32":0,
        "33":0,
        "34":0,
        "35":0,
        "36":0,
        "37":0,
        "38":0,
        "39":0,
        "40":0
    }
    f=[]
    for i in range (0,40):
        f.append(100000000000000);
    
    paths={
        "1":-1,
        "2":-1,
        "3":-1,
        "4":-1,
        "5":-1,
        "6":-1,
        "7":-1,
        "8":-1,
        "9":-1,
        "10":-1,
        "11":-1,
        "12":-1,
        "13":-1,
        "14":-1,
        "15":-1,
        "16":-1,
        "17":-1,
        "18":-1,
        "19":-1,
        "20":-1,
        "21":-1,
        "22":-1,
        "23":-1,
        "24":-1,
        "25":-1,
        "26":-1,
        "27":-1,
        "28":-1,
        "29":-1,
        "30":-1,
        "31":-1,
        "32":-1,
        "33":-1,
        "34":-1,
        "35":-1,
        "36":-1,
        "37":-1,
        "38":-1,
        "39":-1,
        "40":-1
    }
    if (goal==start):
        path.append(goal);
    else:
        h=cal_h(M,goal,i);
        f[start]=h;
        frontier.add(start)
        paths[str(start)]=start
        done=True;
        while (len(frontier)!=0 and done==True):
            q=f.index(min(f))
            f[q]=100000000;
            intersections=M.roads[q]
            for i in range (0,len(intersections)):
                if (goal==intersections[i]):
                    paths[str(intersections[i])]=q;
                    path=find_path(paths,goal,start);
                    done=False;
                    break;
                else:
                    xi,yi= get_coordinates(M,q);
                    x2,y2= get_coordinates (M,intersections[i]);
                    temp_g=g_dict[str(q)]+distance(x2,y2,xi,yi)
                    if ((intersections[i] not in frontier and intersections[i] not in explored) or (temp_g<g_dict[str(intersections[i])])):
                        frontier.add(intersections[i])
                        g_dict[str(intersections[i])]=temp_g
                        f[intersections[i]]=temp_g+cal_h(M,goal,intersections[i])
                        paths[str(intersections[i])]=q;  
            frontier.remove(q)
            explored.add(q)
    return path;

def distance (x2,y2,x1,y1):
    return math.sqrt(pow((x2-x1),2)+pow((y2-y1),2))

def get_coordinates (M,intersection_number):
    points_state=M.intersections[intersection_number]
    state_x=points_state[0]
    state_y=points_state[1]
    return state_x, state_y
                        
def cal_h(M,goal,i):
    xgoal,ygoal= get_coordinates (M,goal);
    xi,yi= get_coordinates (M,i);
    h=distance(xgoal,ygoal,xi,yi);
    return h;

def find_path(paths,goal,start):
    path=[]
    i=goal
    path.append(goal)
    while (i!=start):
        path.append(paths[str(i)]);
        i=paths[str(i)]
    return list(reversed(path));


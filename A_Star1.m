
%CREATING THE 2-D MAP ARRAY
MAX_X=10;
MAX_Y=10;
MAX_VAL=10;
%Objects in each coordinate
MAP=2*(ones(MAX_X,MAX_Y));

% Obtaining Obstacle, Target and Robot Position
% Initialize the MAP with input values
% Obstacle=-1,Target = 0,Robot=1,Space=2

x_val = 1;
y_val = 1;
axis([1 MAX_X+1 1 MAX_Y+1])%gets an axis map
grid on;% adds major grid lines to current axis
hold on;% retains current graph and adds another graph to it


% Initialize MAP with Obstacle, Target, Start Location selection
% Initializing the target coordinates

h=msgbox('Select the Target using the Left Mouse button');% functions as printf function
uiwait(h,10);% stops program execution for 10sec or until target is selected

xlabel('Select the Target using the Left Mouse button','Color','black');
button=0;
while (button ~= 1) %Repeat until the Left button is not clicked, MOUSE left=1,middle=2,right=3
    [xval,yval,button]=ginput(1);% gets 1 input from mouse button
end
xval=floor(xval);%indexing to nearest before value
yval=floor(yval);
xTarget=xval;%X Coordinate of the Target
yTarget=yval;%Y Coordinate of the Target

MAP(xval,yval)=0;%Initialize MAP with location of the target: MAP is matric containing values
plot(xval+.5,yval+.5,'gd');
text(xval+1,yval+.5,'Target')

% Initializing obstacles

h=msgbox('Select Obstacles using the Left Mouse button and select the last obstacle using the Right button');
  xlabel('Select Obstacles using the Left Mouse button and select the last obstacle using the Right button','Color','blue');
uiwait(h,10);

while button == 1
    [xval,yval,button] = ginput(1);
    xval=floor(xval);
    yval=floor(yval);
    MAP(xval,yval)=-1;%Reading obstacles as '-1' 
    plot(xval+.5,yval+.5,'ro');
 end%End of While loop
 
% Initializing vehicle initial position
h=msgbox('Select the Vehicle initial position using the Left Mouse button');
uiwait(h,5);

xlabel('Select the Vehicle initial position ','Color','black');
button=0;
while (button ~= 1) 
    [xval,yval,button]=ginput(1);
    xval=floor(xval);
    yval=floor(yval);
end
xStart=xval;%Starting Position
yStart=yval;
MAP(xval,yval)=1;
 plot(xval+.5,yval+.5,'bd');

 %Target, Obstacles and Initial position are plotted and loaded into matrix
 
%LISTS 

%OPEN LIST FORMAT |X val |Y val |Parent X val |Parent Y val |h(n) |g(n)|f(n)|
OPEN=[];% List of grid cells that have space
%CLOSED LIST STRUCTURE FORMAT %X val | Y val |
CLOSED=[];% List of grid cells that contain obstacles

%Storing obstacle coordinates in the Closed list
k=1;
for i=1:MAX_X
    for j=1:MAX_Y
        if(MAP(i,j) == -1)
            CLOSED(k,1)=i; 
            CLOSED(k,2)=j; 
            k=k+1;
        end
    end
end
CLOSED_COUNT=size(CLOSED,1);% Gives vertical rows size
%set the starting node as the first node
xNode=xval;
yNode=yval;
OPEN_COUNT=1;
path_cost=0;
goal_distance=distance(xNode,yNode,xTarget,yTarget);
OPEN(OPEN_COUNT,:)=insert_open(xNode,yNode,xNode,yNode,path_cost,goal_distance,goal_distance);
OPEN(OPEN_COUNT,1)=0;
CLOSED_COUNT=CLOSED_COUNT+1;
CLOSED(CLOSED_COUNT,1)=xNode;
CLOSED(CLOSED_COUNT,2)=yNode;
% Stored initial vehicke position coordinates into closed list

NoPath=1;
%   FINDING SHORTEST PATH COORDINATES

while((xNode ~= xTarget || yNode ~= yTarget) && NoPath == 1)

 exp_array=expand_array(xNode,yNode,path_cost,xTarget,yTarget,CLOSED,MAX_X,MAX_Y);
 exp_count=size(exp_array,1);
 % exp_array is an m*n matrix with m successor node values
 
 %UPDATING LIST OPEN WITH THE SUCCESSOR NODES
  %EXPANDED ARRAY FORMAT |X val |Y val ||h(n) |g(n)|f(n)|
  for i=1:exp_count
    flag=0;
    for j=1:OPEN_COUNT
        if(exp_array(i,1) == OPEN(j,2) && exp_array(i,2) == OPEN(j,3) )
            OPEN(j,8)=min(OPEN(j,8),exp_array(i,5)); 
            if OPEN(j,8)== exp_array(i,5)
                %UPDATING PARENTS,gn,hn
                OPEN(j,4)=xNode;
                OPEN(j,5)=yNode;
                OPEN(j,6)=exp_array(i,3);
                OPEN(j,7)=exp_array(i,4);
            end;%End of minimum fn check
            flag=1;
        end;%End of node check
    end;%End of j for
    if flag == 0
        OPEN_COUNT = OPEN_COUNT+1;
        OPEN(OPEN_COUNT,:)=insert_open(exp_array(i,1),exp_array(i,2),xNode,yNode,exp_array(i,3),exp_array(i,4),exp_array(i,5));
     end;%End of insert new element into the OPEN list
 end;%End of i for
 
 %END OF WHILE LOOP

 %Finding out the node with the smallest fn 
  index_min_node = min_fn(OPEN,OPEN_COUNT,xTarget,yTarget);
  if (index_min_node ~= -1)    
   %Set xNode and yNode to the node with minimum fn
   xNode=OPEN(index_min_node,2);
   yNode=OPEN(index_min_node,3);
   path_cost=OPEN(index_min_node,6);%Updating the cost of reaching the parent node
  %Move the Node to list CLOSED
  CLOSED_COUNT=CLOSED_COUNT+1;
  CLOSED(CLOSED_COUNT,1)=xNode;
  CLOSED(CLOSED_COUNT,2)=yNode;
  OPEN(index_min_node,1)=0;
  else
      %No path exists to the Target!!
      NoPath=0;%Exits the loop!
  end;%End of index_min_node check
end;%End of While Loop


i=size(CLOSED,1);
Optimal_path=[];
xval=CLOSED(i,1);
yval=CLOSED(i,2);
i=1;
Optimal_path(i,1)=xval;
Optimal_path(i,2)=yval;
i=i+1;

if ( (xval == xTarget) && (yval == yTarget))
    inode=0;
   %Traverse OPEN and determine the parent nodes
   parent_x=OPEN(node_index(OPEN,xval,yval),4);%node_index returns the index of the node
   parent_y=OPEN(node_index(OPEN,xval,yval),5);
   
   while( parent_x ~= xStart || parent_y ~= yStart)
           Optimal_path(i,1) = parent_x;
           Optimal_path(i,2) = parent_y;
           %Get the grandparents:-)
           inode=node_index(OPEN,parent_x,parent_y);
           parent_x=OPEN(inode,4);%node_index returns the index of the node
           parent_y=OPEN(inode,5);
           i=i+1;
    end;
 j=size(Optimal_path,1);
 %Plot the Optimal Path!
 p=plot(Optimal_path(j,1)+.5,Optimal_path(j,2)+.5,'go');
 j=j-1;
 for i=j:-1:1
  pause(.25);
  set(p,'XData',Optimal_path(i,1)+.5,'YData',Optimal_path(i,2)+.5);
 drawnow ;% causes figure windows and their children to update, and flushes the system event queue. 
 end;
 plot(Optimal_path(:,1)+.5,Optimal_path(:,2)+.5);
else
 pause(1);
 h=msgbox('Sorry, No path exists to the Target!','warn');
 uiwait(h,5);
end

    






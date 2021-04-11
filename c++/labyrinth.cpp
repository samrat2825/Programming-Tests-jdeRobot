#include <bits/stdc++.h>
#include <fstream>

using namespace std;
#define CP2 pair<int,int>

void update_next(vector<string> &matrix ,vector<vector<int>> &visited , stack<CP2> &open_stack , deque<CP2> &max_queue)
	{
	    int k, l, x = open_stack.top().first, y=open_stack.top().second, r = matrix.size(), c = matrix[0].length();
		for(k=x-1;k<=x+1;k++){
			for(l=y-1;l<=y+1;l++){                            // scanning for all adjecent blocks 
				if((k==x-1&&l==y-1)||(k==x-1&&l==y+1)||(k==x+1&&l==y+1)||(k==x+1&&l==y-1))
					{
						continue;                                        //skiping Diagonal steps
					}
					
					if(k<0||l<0||k>r-1||l>c-1)
					{       
						continue;                                       // keeping steps in [r][c]
					} 
 					
					if(matrix[k][l]=='.' && visited[k][l]==0 )          //entering in valid blocks
					{          
                        open_stack.push(make_pair(k,l));
					    visited[k][l]=1;                                // making block visited  
					    
						if(open_stack.size()>max_queue.size())			// checking stack size
						{         
								stack<CP2> open_stack_copy = open_stack;    // copying stack to avoid time complexity errors
								max_queue.clear();
								
	                        	while(!open_stack_copy.empty())
								{
                                    max_queue.push_front(open_stack_copy.top());      //adding (x,y) points in dequeue
									open_stack_copy.pop();
								}
						}
                        
						update_next(matrix, visited, open_stack ,max_queue);    // as everything is fine move to next block
					}
				}		
			}                   
			          
	// backtracing starts here..
	visited[x][y]=0;              //making cell unvisited
	if(!open_stack.empty())
	{
        open_stack.pop();        // removing last visited 
    }
}

int main()
{
	ifstream file("schema2.txt");	     // reading schema from txt file
	string a;
	vector<string> matrix;
	while(getline(file, a))
	{
		matrix.push_back(a);
	}
	
	int r = matrix.size(), c = matrix[0].length();
	char num = '0';                                         // its not proper way to use incrementing char(insted of int) but used to keep it simple  
	vector<vector<int>> visited(r,vector<int>(c,0));
    deque<CP2> entry_list;
	stack<CP2> open_stack;
	deque<CP2> max_queue;

    for(int i=0 ;i< r;i++){
        for(int j =0 ; j<c; j++){
            if((i==0 || i==r-1 || j==0 || j==c-1 ) && matrix[i][j] == '.' ){
                entry_list.push_back(make_pair(i,j));               //add (x,y) starting points  
            }
        }
    }
    
    while(!entry_list.empty())										// itering for each starting point
	{                                     
		open_stack.push(entry_list.front());
		visited[open_stack.top().first][open_stack.top().second]=1;
        entry_list.pop_front();
		update_next(matrix, visited, open_stack,max_queue);
	}
	
	cout <<max_queue.size()<< endl;                                 // size of double ended queue 
	
	while(!max_queue.empty()){
		CP2 duo =max_queue.front();
		matrix[duo.first][duo.second] = num;
		num++;                                                   // incrementing char.....
		max_queue.pop_front();
	}
	
	for(int i=0 ;i<r;i++){
        cout<<matrix[i]<<endl;                                  //printing max path(with order) in terminal...
    }
}

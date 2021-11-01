#include <SFML/Graphics.hpp>  
#include <bits/stdc++.h>


int win_size = 500;
int sq_num = 50;
int grid[50][50];
bool visited[50][50];
int sq_size = win_size/sq_num;
bool flag = false;

int main()
{

	std::pair<int,int> start_node;
	std::pair<int,int> end_node;

	std::memset(visited,false,sizeof(visited));
	std::memset(grid,0,sizeof(grid));

	//render window with pixel size and title
	sf::RenderWindow window(sf::VideoMode(win_size, win_size), "Path Grid");

	//grid options-----------------------
	//   2 - start node
	//   3 - end node
	start_node = std::make_pair(10,10);
	end_node = std::make_pair(18,10);

	//Checking grid----------------------

	//	grid[20][30] = 1;

	// Robot ----------------------------

	//draw circle of 100px radius
	sf::CircleShape shape(5.f);
	//circle color green
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(15*sq_size,5*sq_size);


	// Environment ----------------------
	sf::Vector2f position(100, 100);
	sf::Vector2f size(sq_size, sq_size);	

	//rectangle object (Float) or else IntRect
	sf::RectangleShape r;
	r.setSize(size);
	r.setPosition(position);
	r.setFillColor(sf::Color::Red);
	r.setOutlineColor(sf::Color::Black);
	r.setOutlineThickness(1);

	//set framelimit to 0 and enable vsync
	//required for unneccasary single core load
	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(true);


//----------For dijkstra implementation
	int si = start_node.first;
	int sj = start_node.second;
	int ei = end_node.first;
	int ej = end_node.second;


	grid[si][sj] = 2;
	grid[ei][ej] = 3;

	std::queue<std::pair<int,int>> q;
	q.push(start_node);




	//loop while window open
	while (window.isOpen()) { 
		sf::Event event; 
		int posx,posy;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i pos = sf::Mouse::getPosition();
				posx = int(pos.x/sq_size);
				posy = int(pos.y/sq_size);
				if(posx < sq_num && posy <sq_num)
					grid[int(pos.x/sq_size)][int(pos.y/sq_size)-3]=1;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Vector2i pos = sf::Mouse::getPosition();
				posx = int(pos.x/sq_size);
				posy = int(pos.y/sq_size);
				//check title bar selection
				if(posx < sq_num && (posy>3 && posy<sq_num-3))
					grid[int(pos.x/sq_size)][int(pos.y/sq_size)-3]=0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && flag==false)
			{
				flag = true;
//				dijkstra(start_node,end_node);
			}
		}

//-----------------------------------------BFS---------------------------------------------------------




	if(!q.empty()){

		std::pair<int,int> u = q.front();
		q.pop();

		int u_i = u.first;
		int u_j = u.second;
		
		std::cout<<u_i<<" "<<u_j<<"\n";
		visited[u_i][u_j] = true;

		if(u_i==ei && u_j==ej)break;

		if(u_i!=si || u_j!=sj)
			grid[u_i][u_j] = 4;


		if(u_i < sq_num && u_j+1<sq_num && visited[u_i][u_j+1]==false){
			q.push(std::make_pair(u_i,u_j+1));
		}
		if(u_i+1 < sq_num && u_j<sq_num && visited[u_i+1][u_j]==false){
			q.push(std::make_pair(u_i+1,u_j));
		}
		if(u_i-1 >=0 && u_j<sq_num && visited[u_i-1][u_j]==false){
			q.push(std::make_pair(u_i-1,u_j));
		}
		if(u_i < sq_num && u_j-1>=0 && visited[u_i][u_j-1]==false){
			q.push(std::make_pair(u_i,u_j-1));
		}
	}

//-----------------------------------------------------------------------------------------------------------

		window.clear();
		for(int i=0;i<sq_num;i++){
			for(int j=0;j<sq_num;j++){
				if(grid[i][j]==0){
					r.setFillColor(sf::Color::White);
				}
				else if(grid[i][j]==2){	
					r.setFillColor(sf::Color::Red);
				}
				else if(grid[i][j]==3){	
					r.setFillColor(sf::Color::Green);
				}
				else if(grid[i][j]==4){	
					r.setFillColor(sf::Color::Blue);
				}
				else{
					r.setFillColor(sf::Color::Black);
				}
				r.setPosition(sq_size*i,sq_size*j);
				window.draw(r);
			}
		}
	//	window.draw(shape);
		window.display();
	}
	return 0;
}

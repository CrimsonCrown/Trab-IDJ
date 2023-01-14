#include "NavMap.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "AnimationSetter.h"

#define PI 3.1415926

NavMap* NavMap::map;

SearchNode::SearchNode(TileCoords point, float cost) {
	this->point = point;
	this->cost = cost;
}

bool operator<(const SearchNode& n1, const SearchNode& n2) {
	return n1.cost > n2.cost;
}

NavMap::NavMap(GameObject& associated, float tileSize, int x, int y) : Component(associated) {
	this->tileSize = tileSize;
	xsize = x;
	ysize = y;
	mapVacancy = std::vector<bool>(x*y, false);
	map = this;
	return;
}

NavMap::~NavMap() {
	map = nullptr;
	return;
}

void NavMap::Start() {
	return;
}

void NavMap::Update(float dt) {
	return;
}

void NavMap::Render() {
#ifdef DEBUG
	SDL_Point points[5];
	for (int i = 0; i < xsize; i++) {
		for (int j = 0; j < ysize; j++) {
			if (At(i, j)) {
				TileCoords block(i, j);
				Vec2 point = block.Location(tileSize).Sub(Camera::pos);
				points[0] = { (int)point.x, (int)point.y };
				points[4] = { (int)point.x, (int)point.y };
				block.x = block.x + 1;
				point = block.Location(tileSize).Sub(Camera::pos);
				points[1] = { (int)point.x, (int)point.y };
				block.y = block.y + 1;
				point = block.Location(tileSize).Sub(Camera::pos);
				points[2] = { (int)point.x, (int)point.y };
				block.x = block.x - 1;
				point = block.Location(tileSize).Sub(Camera::pos);
				points[3] = { (int)point.x, (int)point.y };

				SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 255, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
			}
		}
	}
#endif
	return;
}

bool NavMap::Is(std::string type) {
	if (type == "NavMap") {
		return true;
	}
	return false;
}

void NavMap::Fill(TileCoords origin, int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (origin.x + i < xsize&&origin.y + j < ysize) {
				mapVacancy[Index(origin.x + i, origin.y + j)] = true;
			}
		}
	}
}

void NavMap::Path(TileCoords start, TileCoords finish, std::deque<TileCoords>& path) {
	path.clear();//caminho de retorno
	std::vector<float> mapCosts = std::vector<float>(xsize*ysize, 9999);//custo do caminho até o ponto
	std::vector<TileCoords> CN = std::vector<TileCoords>(xsize*ysize, {9999,9999});//coordenadas do caminho mais curto
	std::priority_queue<SearchNode> open;//lista de nós para explorar
	float currentcost = 0;
	TileCoords currentcoords = start;
	//define primeiro ponto
	open.push(SearchNode(currentcoords, currentcost + Dist(currentcoords, finish)));
	mapCosts[Index(currentcoords)]=currentcost;
	//enquanto não chegou lá/procurou tudo
	while (open.size() > 0 && Dist(open.top().point, finish) > 0) {
		currentcoords = open.top().point;
		currentcost = mapCosts[Index(currentcoords)];
		//std::cout << "looking for node " << finish.x << " " << finish.y << "\n";
		//std::cout << "exploring node " << currentcoords.x << " " << currentcoords.y << " of cost " << currentcost << " and distance " << Dist(currentcoords, finish) << "\n";
		//getchar();
		//define valores
		float sidecost = currentcost + 1;
		float diagcost = currentcost + Dist({ 0,0 }, { 1,1 });
		TileCoords sidecoords[4];
		sidecoords[0] = {currentcoords.x, currentcoords.y-1};
		sidecoords[1] = { currentcoords.x, currentcoords.y + 1 };
		sidecoords[2] = { currentcoords.x -1 , currentcoords.y };
		sidecoords[3] = { currentcoords.x +1, currentcoords.y };
		TileCoords diagcoords[4][3];
		diagcoords[0][0] = { currentcoords.x + 1, currentcoords.y + 1 };
		diagcoords[0][1] = { currentcoords.x, currentcoords.y + 1 };
		diagcoords[0][2] = { currentcoords.x + 1, currentcoords.y};
		diagcoords[1][0] = { currentcoords.x - 1, currentcoords.y + 1 };
		diagcoords[1][1] = { currentcoords.x, currentcoords.y + 1 };
		diagcoords[1][2] = { currentcoords.x - 1, currentcoords.y };
		diagcoords[2][0] = { currentcoords.x + 1, currentcoords.y - 1 };
		diagcoords[2][1] = { currentcoords.x, currentcoords.y - 1 };
		diagcoords[2][2] = { currentcoords.x + 1, currentcoords.y };
		diagcoords[3][0] = { currentcoords.x - 1, currentcoords.y - 1 };
		diagcoords[3][1] = { currentcoords.x, currentcoords.y - 1 };
		diagcoords[3][2] = { currentcoords.x - 1, currentcoords.y };
		//expande lados
		for (int i = 0; i < 4; i++) {
			//se não está bloqueado, está dentro dos limites, o custo é mais alto
			//std::cout << "try expanding node " << sidecoords[i].x << " " << sidecoords[i].y << " of cost " << sidecost << "\n";
			if ((sidecoords[i].y >= 0 )&&( sidecoords[i].y < ysize )&&( sidecoords[i].x >= 0 )&&( sidecoords[i].x < xsize )&&( mapVacancy[Index(sidecoords[i])] == false )&&( mapCosts[Index(sidecoords[i])] > sidecost)) {
				open.push({ sidecoords[i], sidecost + Dist(sidecoords[i], finish) });
				mapCosts[Index(sidecoords[i])] = sidecost;
				CN[Index(sidecoords[i])] = currentcoords;
				//std::cout << "expanding node " << sidecoords[i].x << " " << sidecoords[i].y << " of cost " << sidecost << "\n";
			}
		}
		//expande diagonais
		for (int i = 0; i < 4; i++) {
			//se não está bloqueado, está dentro dos limites, o custo é mais alto
			if (diagcoords[i][0].y >= 0 && diagcoords[i][0].y < ysize && diagcoords[i][0].x >= 0 && diagcoords[i][0].x < xsize &&
				mapVacancy[Index(diagcoords[i][0])] == false && mapVacancy[Index(diagcoords[i][1])] == false && mapVacancy[Index(diagcoords[i][2])] == false &&
				mapCosts[Index(diagcoords[i][0])] > diagcost) {
				open.push({ diagcoords[i][0], diagcost + Dist(diagcoords[i][0], finish) });
				mapCosts[Index(diagcoords[i][0])] = diagcost;
				CN[Index(diagcoords[i][0])] = currentcoords;
			}
		}
		//deleta elemento
		open.pop();
	}
	//std::cout << "out of path " << open.size() << " " << Dist(open.top().point, finish) << " of cost " << currentcost << "\n";
	//se vazio, não achou ponto final
	if (open.size()==0) {
		return;
	}
	//caso contrario, topo da pilha é o ponto final
	else {
		//encontra caminho de volta
		currentcoords = open.top().point;
		//std::cout << "finished at node " << currentcoords.x << " " << currentcoords.y << "\n";
		// enquanto não voltar a origem
		while (Dist(currentcoords, start) > 0) {
			path.push_front(currentcoords);
			//std::cout << "found a path\n";
			currentcoords = CN[Index(currentcoords)];
		}
		return;
	}
}

int NavMap::Index(int x, int y) {
	return y * xsize + x;
}

int NavMap::Index(TileCoords coords) {
	return coords.y * xsize + coords.x;
}

bool NavMap::At(int x, int y) {
	return mapVacancy[Index(x, y)];
}

float NavMap::Dist(TileCoords a, TileCoords b) {
	return sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
}
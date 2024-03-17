#pragma once
//#ifndef Coordinator_h // 만약 coordinator_h가 정의 되어 있지 않다면
//#define Coordinator_h // coordinator_h를 정의하겠다.

class Coordinator {
private:
	int Ypos, Xpos;
public:
	Coordinator():Ypos(0), Xpos(0) {}
	Coordinator(int y, int x) : Ypos(y), Xpos(x) {}
	~Coordinator() {};
	inline int GetYpos() const { return Ypos; }
	inline int GetXpos() const { return Xpos; }
	inline void MovY(int v) { Ypos += v; }
	inline void MovX(int v) { Xpos += v; }
};

//#endif // !#Coordinator_h
#pragma once
//#ifndef Coordinator_h // ���� coordinator_h�� ���� �Ǿ� ���� �ʴٸ�
//#define Coordinator_h // coordinator_h�� �����ϰڴ�.

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
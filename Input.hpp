#ifndef INPUT_HPP
#define INPUT_HPP

enum eInput
{
	MOUSE = 0,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	VALIDATE,
	ESC,
	NOINPUT,
};

class Input
{
public:
	Input();
	Input(eInput);
	Input(eInput, int, int);
	Input(Input const & src);
	void SetType(eInput type);
	Input& operator=(Input const & rhs);
	eInput GetType();
	int GetX();
	int GetY();
	~Input();

private:
	eInput input;
	int x;
	int y;
};

#endif

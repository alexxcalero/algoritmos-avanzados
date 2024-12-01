#ifndef TAREA_H
#define TAREA_H

#include <vector>
using namespace std;

class Tarea {
public:
	Tarea(int id, const vector<int> &tiemposProcesamiento);
	Tarea(const Tarea &orig);
	virtual ~Tarea();
    void SetTiemposProcesamiento(vector<int> tiemposProcesamiento);
    vector<int> GetTiemposProcesamiento() const;
    void SetId(int id);
    int GetId() const;
private:
	int id;
	vector<int> tiemposProcesamiento;
};

#endif /* TAREA_H */

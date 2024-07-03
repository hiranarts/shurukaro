#pragma once

struct Component{
	size_t _size_of_struct;
	int _flag;
	int _length = 0;
	int _capacity;
	//sparse is a takes an ent_id as a key and returns the index inside the packed array
	phmap::flat_hash_map<int, int> _sparse;
	void* _packed;
	Component(size_t struct_size, int array_size, int c_flag) {
		_size_of_struct = struct_size;
		_capacity = array_size;
		_flag = c_flag;
		_sparse.reserve(_capacity);
		_packed = malloc(_capacity * _size_of_struct);
		memset(_packed, 0, _capacity * _size_of_struct);
		printf("Size of component is %zu\n", _size_of_struct * _capacity);
	}
	~Component() {
		free(_packed);
	}
	void debugInfo() {
		for (auto patch : _sparse) {
		std::cout << "\" " << patch.first << ": " << patch.second << " \"";
		}
		std::cout << std::endl;
	}
	void Destroy() {
		printf("Component %d is being destroyed\n", _flag);
		free(_packed);
	}

	void Reset() {
		printf("Component %d is being reset\n", _flag);
		memset(_packed, 0, _capacity * _size_of_struct);
	}

	void* at(int index) {
		return (char*)_packed + (index * _size_of_struct);
	}
	void* query(int ent_id) {
		if (_sparse.contains(ent_id)) {
			return at(_sparse[ent_id]);
		}
		printf("ERROR: ENT_ID %d not in COMPONENT %d\n", ent_id, _flag);
		return NULL;
	}
	void append(int ent_id, int* ent_flag, void* data, int size_of_data) {
		if (size_of_data != _size_of_struct) {
			printf("ERROR DATA NOT CORRECT SIZE \n");
			return;
		}
		//append at end
		memcpy(at(_length), data, _size_of_struct);
		//add to sparse 
		_sparse[ent_id] = _length;;
		_length++;
	//	*ent_flag |= _flag;
	}
	//finds which entity is at the index in the _packed array. the argument is the index in the PACKED ARRAY
	int whichEntity(int index) {
		for (auto i : _sparse) {
			if (i.second == index) {
				return i.first;
			}
		}
		return -1;
	}
	void remove(int ent_id, int* ent_flag) {
		if (_sparse.contains(ent_id)) {
			//printf("removing ent id %d\n", ent_id);
			int index = _sparse[ent_id];
			//swap
			memcpy(at(index), at(_length - 1), _size_of_struct);
			//set new index for tail entity
			_sparse[whichEntity(_length - 1)] = index;
			memset(at(_length), 0, _size_of_struct);
			_length--;
			_sparse.erase(ent_id);
			*ent_flag &= ~_flag;
		}

	}
};

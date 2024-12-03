class Slab:
    def __init__(self, object_size, object_per_slab = 10):
        self.slabs = []
        self.object_size = object_size
        self.object_per_slab = object_per_slab
        self._internal_alloc()
    
    def _internal_alloc(self):
        slab = {
            "memory": bytearray(self.object_size * self.object_per_slab),
            "avaiable": set(range(self.object_per_slab)) # {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
        }
        self.slabs.append(slab)

    def alloc(self):
        for slab in self.slabs:
            if slab["avaiable"]: # if len(slab["avaiable"]) != 0
                index = slab["avaiable"].pop()
                return (slab, index)

        self._internal_alloc()
        return self.alloc()

    def free(self, slab, index):
        slab["avaiable"].add(index)

struct_size = 200   #   bytes
allocator = Slab(struct_size)
slav, index = allocator.alloc()
allocator.free(slab, index)
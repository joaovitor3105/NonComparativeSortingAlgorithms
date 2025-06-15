# structures/queue_linear.py
from typing import List, Tuple
import sys
sys.path.append('..')
from utils.data_structure import DataStructure


class QueueLinear(DataStructure):
    """Fila com alocação linear (array circular)"""
    
    def __init__(self, capacity: int):
        self.data = [0] * capacity
        self.front = 0
        self.rear = -1
        self._size = 0
        self.capacity = capacity
    
    def enqueue(self, value: int) -> None:
        if self._size < self.capacity:
            self.rear = (self.rear + 1) % self.capacity
            self.data[self.rear] = value
            self._size += 1
    
    def dequeue(self) -> Tuple[int, bool]:
        if self._size == 0:
            return 0, False
        
        value = self.data[self.front]
        self.front = (self.front + 1) % self.capacity
        self._size -= 1
        return value, True
    
    def to_array(self) -> List[int]:
        result = []
        for i in range(self._size):
            index = (self.front + i) % self.capacity
            result.append(self.data[index])
        return result
    
    def from_array(self, arr: List[int]) -> None:
        self.front = 0
        self.rear = -1
        self._size = 0
        
        for v in arr:
            self.enqueue(v)
    
    def size(self) -> int:
        return self._size
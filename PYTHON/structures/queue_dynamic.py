# structures/queue_dynamic.py
from typing import List, Optional, Tuple
import sys
sys.path.append('..')
from utils.data_structure import DataStructure


class NodeQueue:
    """Nó para fila encadeada"""
    def __init__(self, value: int):
        self.value = value
        self.next: Optional['NodeQueue'] = None


class QueueDynamic(DataStructure):
    """Fila com alocação dinâmica (lista encadeada)"""
    
    def __init__(self):
        self.front: Optional[NodeQueue] = None
        self.rear: Optional[NodeQueue] = None
        self._size = 0
    
    def enqueue(self, value: int) -> None:
        new_node = NodeQueue(value)
        
        if self.rear is None:
            self.front = new_node
            self.rear = new_node
        else:
            self.rear.next = new_node
            self.rear = new_node
        
        self._size += 1
    
    def dequeue(self) -> Tuple[int, bool]:
        if self.front is None:
            return 0, False
        
        value = self.front.value
        self.front = self.front.next
        
        if self.front is None:
            self.rear = None
        
        self._size -= 1
        return value, True
    
    def to_array(self) -> List[int]:
        result = []
        current = self.front
        
        while current is not None:
            result.append(current.value)
            current = current.next
        
        return result
    
    def from_array(self, arr: List[int]) -> None:
        self.front = None
        self.rear = None
        self._size = 0
        
        for v in arr:
            self.enqueue(v)
    
    def size(self) -> int:
        return self._size
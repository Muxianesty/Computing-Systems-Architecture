# ------------------------------------------------------------------------------
# PlantContainer.py - provides declaration and implementation for the container
# of plants-classes and functions working with it.
# ------------------------------------------------------------------------------
import random
from typing import TextIO
from plants.Plant import Plant
from plants.Bush import Bush
from plants.Flower import Flower
from plants.Tree import Tree


class PlantContainer(object):
    MAX_CAPACITY_ = 10000

    # def __init__(self):
    #     self.plants_ = []
    #     self.capacity_ = 0
    #     self.current_size_ = 0

    def __init__(self, capacity: int) -> None:
        """
        Default "plant-container"-object constructor for a specific capacity.

        :param capacity: Integer parameter, specifying the size of a container to create.
        """
        # self.__init__()
        self.plants_ = []
        self.capacity_ = 0
        self.current_size_ = 0
        if (capacity < 0) or (capacity > PlantContainer.MAX_CAPACITY_):
            print(f"!!!Value {capacity} is less than 0 or more than {PlantContainer.MAX_CAPACITY_} and cannot "
                  f"be used as!!!\n!!!container capacity - value '0' will be used instead!!!")
            self.capacity_ = 0
            return
        self.capacity_ = capacity

    def inputFromFileOrRnd(self, is_random: bool, file: TextIO = 0) -> None:
        """
        Fills the container depending on the flag (with random values or from file).

        :param is_random: Logical parameter, specifying if the input-values come from random generation or from files.

        :param file: Optional parameter, specifying the file to read input values from.

        :return: -
        """
        while self.current_size_ < self.capacity_:
            plant_type = 0
            # Deducing a given type given by the selected way of input.
            params = []
            if is_random:
                plant_type = random.randint(1, 3)
            else:
                params = file.readline().split(' ')
                if params.__len__() > 1:
                    plant_type = abs(int(params[0]))
                    plant_type = plant_type % 3 + 1 if ((plant_type > 3) or (plant_type == 0)) else plant_type
            new_plant = 0
            if plant_type == 1:
                new_plant = Bush(is_random, params)
            elif plant_type == 2:
                new_plant = Flower(is_random, params)
            elif plant_type == 3:
                new_plant = Tree(is_random, params)
            if plant_type == 0 or new_plant == 0:
                print(f"Wrong input on the plant #{self.current_size_ + 1}!")
                self.capacity_ -= 1
                continue
            self.plants_.append(new_plant)
            self.current_size_ += 1

    def containerOutput(self, file: TextIO) -> None:
        """
        Puts the container data to the selected output-file.

        :param file: File parameter, specifying where to put container data to.

        :return: -
        """
        file.write(f"Plant container with {self.current_size_} elements:\n")
        for index in range(self.current_size_):
            file.write(self.plants_[index].toString() + "\n")

    def containerBinarySearch(self, proportion: float, left_border: int, right_border: int) -> int:
        """
        Finds a suitable index in the container array to put the needed item to.

        :param proportion: A value used for comparison during the binary search.

        :param left_border: Left border-index.

        :param right_border: Right border-index.

        :return: An index in the container array where a new item has to be put to.
        """
        if left_border >= right_border:
            return left_border
        middle_index: int = int((left_border + right_border) / 2)
        copy: Plant = self.plants_[middle_index]
        if copy.vowel_count_proportion_ == proportion:
            return middle_index
        return self.containerBinarySearch(proportion, middle_index + 1, right_border) if \
            (proportion > copy.vowel_count_proportion_) else self.containerBinarySearch(proportion, left_border,
                                                                                        middle_index)

    def containerBinaryInsertionSort(self) -> None:
        """
        Sorts the container using Binary Insertion Sort (Insertion Sort with implemented Binary Search O(n*log(n))).

        :return: -
        """
        for index in range(self.current_size_):
            copy: Plant = self.plants_[index]
            new_pos_index = self.containerBinarySearch(copy.vowel_count_proportion_, 0, index)
            current_index: int = index
            while new_pos_index < current_index:
                self.plants_[current_index] = self.plants_[current_index - 1]
                current_index -= 1
            self.plants_[new_pos_index] = copy

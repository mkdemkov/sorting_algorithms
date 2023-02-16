//
// Created by Михаил Демков on 16.02.2023.
//

#ifndef KDZ1__ENUM_H_
#define KDZ1__ENUM_H_

/**
 * почти отсортированный массив - массив, отсортированный наполовину со значениями от 0 до 4000
 * обратно отсортированный массив заполнен значениями от 0 до 4000
 */
enum typeOfArray {
    RANDOM_0_5,
    RANDOM_0_4000,
    ALMOST_SORTED,
    SORTED_DESCENDING
};

#endif //KDZ1__ENUM_H_

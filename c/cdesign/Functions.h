#ifndef CDESIGN_FUNCTIONS_H
#define CDESIGN_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

//查询指令的宏定义
#define EXIT 0
#define SEARCH_BUILDINGS 1
#define SEARCH_ONE_BUILDING 2
#define SEARCH_ROOM 3
#define ADD_BUILDINGS 4
#define ADD_ONE_BUILDING 5
#define ADD_ROOM 6
#define DEL_BUILDINGS 7
#define DEL_ONE_BUILDING 8
#define DEL_ROOM 9

// 给出一些参数，在实际使用中使用指针指向常量比创建字符数组会好一点
// 房屋结构不做限制
const char *const houseModels[] = {"不限", "一室", "两室", "三室", "四室", "五室", "五室以上"};
// 测试数据调7个吧。东湖高新区", "洪山区", "江岸区", "东西湖区", "汉阳区", "武昌区", "江汉区"
const char *const houseLocations[] = {"不限", "东湖高新区", "洪山区", "江岸区", "东西湖区", "汉阳区", "武昌区", "江汉区"};

typedef int bool;
const bool false = 0;
const bool true = 1;
struct House;
struct OneBuilding;
struct Buildings;

typedef struct House {
    int house_id;
    char model[100];
    float area;
//    float average_rate;
    float prize;
    struct House *next;
    int building_id;
    int buildings_id;
} House;
typedef House *HousePtr;

typedef struct OneBuilding {
    int one_building_id;
//    char unit[100];
    int floorCount;
    House *head;
    struct OneBuilding *next;
    int buildings_id;
} OneBuilding;
typedef OneBuilding *OneBuildingPtr;

typedef struct Buildings {
    int buildings_id;
    char name[100];
    int location_id;
    char location[200];
    char developers[100];
    OneBuilding *head;
    struct Buildings *next;
} Buildings;
typedef Buildings *BuildingsPtr;

BuildingsPtr readBuildings(FILE *file ,int id) {
    BuildingsPtr temp = (BuildingsPtr)malloc(sizeof(Buildings));
    assert(temp != NULL);
    temp->next = NULL;
    temp->buildings_id = id;
    fscanf(file, "%s", temp->name);
    fscanf(file, "%d", &temp->location_id);
    fscanf(file, "%s", temp->location);
    fscanf(file, "%s", temp->developers);
    return temp;
}

OneBuildingPtr readOneBuilding(FILE *file, int id) {
    OneBuildingPtr temp = (OneBuildingPtr) malloc(sizeof(OneBuilding));
    assert(temp != NULL);
    temp->next = NULL;
    temp->one_building_id = id;
    fscanf(file, "%d", &temp->floorCount);
    fscanf(file, "%d", &temp->buildings_id);
    return temp;
}

HousePtr readHouse(FILE *file, int id) {
    HousePtr temp = (HousePtr) malloc(sizeof(House));
    assert(temp != NULL);
    temp->next = NULL;
    fscanf(file, "%s", temp->model);
    fscanf(file, "%f", &temp->area);
    fscanf(file, "%f", &temp->prize);
    fscanf(file, "%d", &temp->building_id);
    fscanf(file, "%d", &temp->buildings_id);
}

BuildingsPtr initialize() {
    FILE *buildings = fopen("buildings.dat", "r");
    FILE *oneBuilding = fopen("oneBuilding.dat", "r");
    FILE *house = fopen("house.dat", "r");
    assert(buildings != NULL);
    assert(oneBuilding != NULL);
    assert(house != NULL);

    BuildingsPtr buildingsTemp;
    BuildingsPtr buildingsHead;
    int id = 0;
    bool first = true;
    while (fscanf(buildings, "%d", &id) != EOF) {
        if (first) {
            buildingsHead = buildingsTemp = readBuildings(buildings, id);
            first = false;
        } else {
            buildingsTemp = buildingsTemp->next = readBuildings(buildings, id);
        }
    }

    OneBuildingPtr oneBuildingTemp;
    first = true;
    while (fscanf(oneBuilding, "%d", &id) != EOF) {
        if (first) {
            oneBuildingTemp = readOneBuilding(oneBuilding, id);
            buildingsTemp = buildingsHead;
            while (buildingsTemp != NULL && buildingsTemp->buildings_id != oneBuildingTemp->buildings_id) {
                buildingsTemp = buildingsTemp->next;
            }
            assert(buildingsTemp != NULL);
            buildingsTemp->head = oneBuildingTemp;
            first = false;
        } else {
            OneBuildingPtr temp = readOneBuilding(oneBuilding, id);
            if (temp->buildings_id == oneBuildingTemp->buildings_id) {
                oneBuildingTemp = oneBuildingTemp->next = temp;
            } else {
                buildingsTemp = buildingsHead;
                while (buildingsTemp != NULL && buildingsTemp->buildings_id != temp->buildings_id) {
                    buildingsTemp = buildingsTemp->next;
                }
                assert(buildingsTemp != NULL);
                oneBuildingTemp = buildingsTemp->head = temp;
            }
        }
    }

    HousePtr houseTemp;
    first = true;
    while (fscanf(house, "%d", &id) != EOF) {
        if (first) {
            houseTemp = readHouse(house, id);
            houseTemp->house_id = id;
            fscanf(house, "%s", houseTemp->model);
            fscanf(house, "%f", &houseTemp->area);
            fscanf(house, "%f", &houseTemp->prize);
            fscanf(house, "%d", &houseTemp->building_id);
            fscanf(house, "%d", &houseTemp->buildings_id);
            // 先找楼盘再找楼栋
            buildingsTemp = buildingsHead;
            while (buildingsTemp != NULL && buildingsTemp->buildings_id != houseTemp->buildings_id) {
                buildingsTemp = buildingsTemp->next;
            }
            assert(buildingsTemp != NULL);
            oneBuildingTemp = buildingsTemp->head;
            while (oneBuildingTemp != NULL && oneBuildingTemp->one_building_id != houseTemp->building_id) {
                oneBuildingTemp = oneBuildingTemp->next;
            }
            assert(oneBuildingTemp != NULL);
            oneBuildingTemp->head = houseTemp;
            first = false;
        } else {
            HousePtr temp = readHouse(house, id);
            if (houseTemp->building_id == temp->building_id) {
                houseTemp = houseTemp->next = temp;
            } else {
                buildingsTemp = buildingsHead;
                while (buildingsTemp != NULL && buildingsTemp->buildings_id != temp->buildings_id) {
                    buildingsTemp = buildingsTemp->next;
                }
                assert(buildingsTemp != NULL);
                oneBuildingTemp = buildingsTemp->head;
                while (oneBuildingTemp != NULL && oneBuildingTemp->one_building_id != temp->building_id) {
                    oneBuildingTemp = oneBuildingTemp->next;
                }
                assert(oneBuildingTemp != NULL);
                houseTemp = oneBuildingTemp->head;
                if (houseTemp == NULL) {
                    houseTemp = oneBuildingTemp->head = temp;
                } else {
                    while (houseTemp->next != NULL) {
                        houseTemp = houseTemp->next;
                    }
                    houseTemp = houseTemp->next = temp;
                }
            }
        }
    }

    fclose(buildings);
    fclose(oneBuilding);
    fclose(house);
    return buildingsHead;
}


void printBuildings(const BuildingsPtr head) {
    BuildingsPtr temp = head;
    while (temp != NULL) {
        printf("楼盘编号：%02d\n楼盘名称：%s\n楼盘位置：%s %s\n开发商：%s\n\n",
               temp->buildings_id, temp->name, houseLocations[temp->location_id], temp->location, temp->developers);
        temp = temp->next;
    }
}

// 提供菜单选项
int selectChoice() {
    // 设置大一点防止缓冲区溢出
    char choice[1024];
    // 输出提示
    printf("请输入您要进行的操作的编号：\n");
    printf("1：查询楼盘\t");
    printf("2：查询楼栋\t");
    printf("3：查询户型\n");
    printf("4：增加楼盘\t");
    printf("5：增加楼栋\t");
    printf("6：增加户型\n");
    printf("7：删除楼盘\t");
    printf("8：删除楼栋\t");
    printf("9：删除户型\n");
    printf("0：退出系统\n");
    // 接受输入
    scanf("%s", choice);
    // 判断是否全部是数字
    for (size_t i = 0, len = strlen(choice); i < len; ++i) {
        // 不是数字报错，递归返回
        if (!isdigit(choice[i])) {
            printf("输入错误，请重新输入\n");
            return selectChoice();
        }
    }
    // 转换成数字返回
    return atoi(choice);
}

// 搜索符合条件的楼盘
void searchBuildings(const BuildingsPtr head) {

}

// 搜索符合条件的楼栋
void searchOneBuilding(const BuildingsPtr head) {

}

// 寻找户型
void searchRoom(const BuildingsPtr head) {

}

// 添加楼盘
void addBuildings(const BuildingsPtr *head) {

}

// 添加楼栋
void addOneBuilding(const BuildingsPtr head) {

}

// 添加户型
void addRoom(const BuildingsPtr head) {

}

// 删除楼盘
void delBuildings(BuildingsPtr *head) {

}


// 删除楼栋
void delOneBuilding(const BuildingsPtr head) {

}

// 删除户型
void delRoom(const BuildingsPtr head) {

}

// 提供操作
void operations(BuildingsPtr *headp) {
    int choice = 0;
    // 设置结束的标记
    bool isEnd = false;
    while (!isEnd) {
        // 通过函数获取选项
        choice = selectChoice();
        // switch跳转到对应的操作去
        switch (choice) {
            case EXIT:
                // 选择退出就将结束标记设置为true
                isEnd = true;
                //询问是否保存修改的了的数据
                // TODO
                break;
            case SEARCH_BUILDINGS:
                // 跳转到搜索的函数，下同
                searchBuildings(*headp);
                break;
            case SEARCH_ONE_BUILDING:
                searchOneBuilding(*headp);
                break;
            case SEARCH_ROOM:
                searchRoom(*headp);
                break;
            case ADD_BUILDINGS:
                // 添加的函数，下同
                addBuildings(headp);
                break;
            case ADD_ONE_BUILDING:
                addOneBuilding(*headp);
                break;
            case ADD_ROOM:
                addRoom(*headp);
                break;
            case DEL_BUILDINGS:
                // 删除的函数，下同
                delBuildings(headp);
                break;
            case DEL_ONE_BUILDING:
                delOneBuilding(*headp);
                break;
            case DEL_ROOM:
                delRoom(*headp);
                break;
            default:
                // 调到这里说明输入数字不在上面的操作中，给予提示
                printf("无此选项，请重新输入");
        }
    }
}

#endif //CDESIGN_FUNCTIONS_H





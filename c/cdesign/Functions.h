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

const char *const houseModels[] = {"不限", "1室", "2室", "3室", "4室", "5室", "6室及以上"};
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
    float prize;
    struct House *next;
    int building_id;
    int buildings_id;
} House;
typedef House *HousePtr;

typedef struct OneBuilding {
    int one_building_id;
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

BuildingsPtr readBuildings(FILE *file, int id) {
    BuildingsPtr temp = (BuildingsPtr) malloc(sizeof(Buildings));
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
    temp->house_id = id;
    fscanf(file, "%s", temp->model);
    fscanf(file, "%f", &temp->area);
    fscanf(file, "%f", &temp->prize);
    fscanf(file, "%d", &temp->building_id);
    fscanf(file, "%d", &temp->buildings_id);
    return temp;
}

bool startWith(const char *target, const char *sub) {
    size_t str_len = strlen(target);
    size_t sub_len = strlen(sub);
    if (sub_len > str_len) return false;
    for (size_t i = 0; i < sub_len; ++i) {
        if (sub[i] != target[i]) {
            return false;
        }
    }
    return true;
}

// 读取数据的函数
BuildingsPtr initialize() {
    // 首先打开文件
    FILE *buildings = fopen("buildings.dat", "r");
    FILE *oneBuilding = fopen("oneBuilding.dat", "r");
    FILE *house = fopen("house.dat", "r");
    // 断言：文件打开成功
    assert(buildings != NULL);
    assert(oneBuilding != NULL);
    assert(house != NULL);

    // 开始读入楼盘信息
    BuildingsPtr buildingsTemp;
    BuildingsPtr buildingsHead;
    int id = 0;
    // first标志是否是第一个
    bool first = true;
    // 读入楼盘编号成功就能判断有数据
    while (fscanf(buildings, "%d", &id) != EOF) {
        if (first) {
            // 我选择使用函数读入，分配空间读入数据什么的让别的函数去做
            buildingsHead = buildingsTemp = readBuildings(buildings, id);
            // first置为false
            first = false;
        } else {
            // 直接向下接就行了
            buildingsTemp = buildingsTemp->next = readBuildings(buildings, id);
        }
    }

    // 读入楼栋信息
    OneBuildingPtr oneBuildingTemp;
    // 同理
    first = true;
    while (fscanf(oneBuilding, "%d", &id) != EOF) {
        if (first) {
            oneBuildingTemp = readOneBuilding(oneBuilding, id);
            buildingsTemp = buildingsHead;
            // 寻找对应的楼盘
            while (buildingsTemp != NULL && buildingsTemp->buildings_id != oneBuildingTemp->buildings_id) {
                buildingsTemp = buildingsTemp->next;
            }
            // 断言对应楼盘存在
            assert(buildingsTemp != NULL);
            // 直接讲head置为读取的数据即可
            buildingsTemp->head = oneBuildingTemp;
            first = false;
        } else {
            OneBuildingPtr temp = readOneBuilding(oneBuilding, id);
            // 如果读入楼栋的楼盘id与前一个相同就直接接上去
            if (temp->buildings_id == oneBuildingTemp->buildings_id) {
                oneBuildingTemp = oneBuildingTemp->next = temp;
            }
                // 否则需要重新寻找对应楼盘
            else {
                buildingsTemp = buildingsHead;
                while (buildingsTemp != NULL && buildingsTemp->buildings_id != temp->buildings_id) {
                    buildingsTemp = buildingsTemp->next;
                }
                // 再次断言
                assert(buildingsTemp != NULL);
                oneBuildingTemp = buildingsTemp->head;
                // 如果此楼盘的楼栋还未创建
                if (oneBuildingTemp == NULL) {
                    oneBuildingTemp = buildingsTemp->head = temp;
                } else {
                    // 如果已经创建就接到尾部
                    while (oneBuildingTemp->next != NULL) {
                        oneBuildingTemp = oneBuildingTemp->next = temp;
                    }
                }
            }
        }
    }

    // 读取房子信息，与上类似
    HousePtr houseTemp;
    first = true;
    while (fscanf(house, "%d", &id) != EOF) {
        if (first) {
            houseTemp = readHouse(house, id);
            // 先找楼盘再找楼栋
            buildingsTemp = buildingsHead;
            // 寻找有对应编号的楼盘
            while (buildingsTemp != NULL && buildingsTemp->buildings_id != houseTemp->buildings_id) {
                buildingsTemp = buildingsTemp->next;
            }
            // 断言楼盘存在
            assert(buildingsTemp != NULL);
            oneBuildingTemp = buildingsTemp->head;
            // 寻找楼栋
            while (oneBuildingTemp != NULL && oneBuildingTemp->one_building_id != houseTemp->building_id) {
                oneBuildingTemp = oneBuildingTemp->next;
            }
            assert(oneBuildingTemp != NULL);
            // 由于是第一个读入的，可以直接设置为head
            oneBuildingTemp->head = houseTemp;
            first = false;
        } else {
            HousePtr temp = readHouse(house, id);
            // 同上，相同的楼盘楼栋号可以考虑直接接上去
            if (houseTemp->building_id == temp->building_id && houseTemp->buildings_id == temp->buildings_id) {
                houseTemp = houseTemp->next = temp;
            } else {
                // 否则需要重新查找楼盘和楼栋
                // 寻找对应楼盘
                buildingsTemp = buildingsHead;
                while (buildingsTemp != NULL && buildingsTemp->buildings_id != temp->buildings_id) {
                    buildingsTemp = buildingsTemp->next;
                }
                assert(buildingsTemp != NULL);
                oneBuildingTemp = buildingsTemp->head;
                // 寻找楼盘中对应的楼栋
                while (oneBuildingTemp != NULL && oneBuildingTemp->one_building_id != temp->building_id) {
                    oneBuildingTemp = oneBuildingTemp->next;
                }
                assert(oneBuildingTemp != NULL);
                houseTemp = oneBuildingTemp->head;
                // 如果还未创建新的房子节点
                if (houseTemp == NULL) {
                    houseTemp = oneBuildingTemp->head = temp;
                } else {
                    // 已经创建了就接到后面去
                    while (houseTemp->next != NULL) {
                        houseTemp = houseTemp->next;
                    }
                    houseTemp = houseTemp->next = temp;
                }
            }
        }
    }

    // 关闭文件
    fclose(buildings);
    fclose(oneBuilding);
    fclose(house);
    return buildingsHead;
}

// 打印输出读取的楼盘信息，调试时使用
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
int searchBuildings(const BuildingsPtr head) {
    printf("输入要找的楼盘所属地区：\n");
    int index = 0;
    char temp[1024] = {0};
    for (int i = 0; i < sizeof(houseLocations) / sizeof(houseLocations[0]); ++i) {
        printf("%d：%s\t", i, houseLocations[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    scanf("%s", temp);
    index = atoi(temp);
    if (index >= sizeof(houseLocations) / sizeof(houseLocations[0]) || index < 0) {
        printf("输入数据超出范围\n");
        return searchBuildings(head);
    }
    BuildingsPtr tempPtr = head;
    int sum = 0;
    while (tempPtr != NULL) {
        if (tempPtr->location_id == index || index == 0) {
            ++sum;
            printf("楼盘编号：%d\n楼盘名称：%s\n地区：%s %s\n开发商：%s\n\n",
                   tempPtr->buildings_id, tempPtr->name, houseLocations[tempPtr->location_id],
                   tempPtr->location, tempPtr->developers);
            if (sum % 3 == 0) {
                printf("输入y继续输出，其它字母停止输出：");
                char ch;
                getchar();
                scanf("%c", &ch);
//                printf("get the char: %c\n", ch);
                if (ch == 'y') {
                    continue;
                }
                break;

            }
        }
        tempPtr = tempPtr->next;
    }
    printf("查询完毕，返回主菜单\n");
    return 0;
}

// 搜索符合条件的楼栋
int searchOneBuilding(const BuildingsPtr head) {
    printf("\n");
    for (size_t i = 0, sum = 0; i < sizeof(houseLocations) / sizeof(houseLocations[0]); ++i) {
        printf("%lu：%s\t", i, houseLocations[i]);
        ++sum;
        if (sum % 3 == 0) {
            printf("\n");
        }
    }
    printf("请输入你想要找的区域id：\n");
    printf("\n");

    int targetRegion;
    scanf("%d", &targetRegion);
    printf("请输入您希望的楼层高度区间（例：10 30）：");
    int low = 0, high = 0;
    scanf("%d %d", &low, &high);
    BuildingsPtr temp = head;
    bool isEnd = false;
    int sum = 0;
    while (temp != NULL && !isEnd) {
        OneBuildingPtr oneBuildingTemp = temp->head;
        while (oneBuildingTemp != NULL && !isEnd) {
            if ((temp->location_id == targetRegion || targetRegion == 0)
                && oneBuildingTemp->floorCount >= low && oneBuildingTemp->floorCount <= high) {
                printf("楼盘id及名称：%d %s\n楼栋id：%d\n楼层高度：%d\n\n", temp->buildings_id, temp->name,
                       oneBuildingTemp->buildings_id, oneBuildingTemp->floorCount);
                ++sum;
                if (sum % 3 == 0) {
                    printf("输入y继续输出，其它字母停止输出：");
                    char ch;
                    getchar();
                    scanf("%c", &ch);
                    printf("get the char: %c\n", ch);
                    if (ch == 'y') {
                        continue;
                    }
                    isEnd = true;
                }
            }
            oneBuildingTemp = oneBuildingTemp->next;
        }
        temp = temp->next;
    }

    printf("查询楼栋完毕，返回主菜单\n");

    return 0;
}

// 搜索符合条件的户型
int searchRoom(const BuildingsPtr head) {
    printf("请输入您要查找的户型：\n");
    for (size_t i = 0; i < sizeof(houseModels) / sizeof(houseModels[0]); ++i) {
        printf("%lu：%s\n", i, houseModels[i]);
    }
    int target = 0;
    char chs[1024];
    scanf("%s", chs);
    if (!isdigit(chs[0])) {
        printf("输入错误请重新输入\n");
        return searchRoom(head);
    }
    target = atoi(chs);
    printf("请输入您希望的价格区间（万元，例：100 150）:");
    int low = 0, high = 0;
    scanf("%d %d", &low, &high);

    int sum = 0;
    bool isEnd = false;
    BuildingsPtr temp = head;
//    printf("%d\n", target);
    while (temp != NULL && !isEnd) {
        OneBuildingPtr oneBuildingTemp = temp->head;
        while (oneBuildingTemp != NULL && !isEnd) {
            HousePtr houseTemp = oneBuildingTemp->head;
            while (houseTemp != NULL && !isEnd) {
                if ((houseTemp->model[0] - '0' == target || target == 0)
                    && houseTemp->prize >= low && houseTemp->prize <= high) {
                    printf("楼盘名称：%s\n房子编号：%d\n面积及户型：%.2f %s\n价格：%.2f\n地理位置：%s %s\n\n",
                           temp->name, houseTemp->house_id, houseTemp->area, houseTemp->model, houseTemp->prize,
                           houseLocations[temp->location_id], temp->location);
                    ++sum;
                    if (sum % 3 == 0) {
                        printf("输入y继续输出，其它字母停止输出：");
                        char ch;
                        getchar();
                        scanf("%c", &ch);
                        printf("get the char: %c\n", ch);
                        if (ch == 'y') {
                            continue;
                        }
                        isEnd = true;
                    }
                }
//                printf("%d\n", houseTemp->house_id);
                houseTemp = houseTemp->next;
            }
//            printf("%d\n", )
            oneBuildingTemp = oneBuildingTemp->next;
        }
//        printf("%d\n", temp->buildings_id);
        temp = temp->next;
    }

    printf("查询完毕，返回主菜单\n");

    return 0;

}

// 添加楼盘
void addBuildings(const BuildingsPtr head) {
    BuildingsPtr temp = (BuildingsPtr) malloc(sizeof(Buildings));
    BuildingsPtr nail = head;
    while (nail->next != NULL)nail = nail->next;
    temp->next = NULL;
    nail->next = temp;
    /*
    typedef struct Buildings {
        int buildings_id;
        char name[100];
        int location_id;
        char location[200];
        char developers[100];
        OneBuilding *head;
        struct Buildings *next;
    } Buildings;
     * */
    printf("现有最大编号：%d\n", nail->buildings_id);
    printf("请输入要加入的楼盘的编号：");
    scanf("%d", &temp->buildings_id);
    printf("请输入要加入的楼盘的名称：");
    scanf("%s", temp->name);
    printf("请输入要加入的楼盘的所属区域id：\n");
    for (size_t i = 1, sum = 0; i < sizeof(houseLocations) / sizeof(houseLocations[0]); ++i) {
        printf("%lu：%s\t", i, houseLocations[i]);
        ++sum;
        if (sum % 3 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    scanf("%d", &temp->location_id);
    printf("请输入开发商名称（不要有空格）：");
    scanf("%s", temp->developers);
    printf("加入完成，返回主菜单\n");
}

// 添加楼栋
void addOneBuilding(const BuildingsPtr head) {
    int sum = 0;
    printf("已有楼盘数据如下：\n");
    BuildingsPtr temp = head;
    while (temp != NULL) {
        printf("编号及名称：%d %s\t", temp->buildings_id, temp->name);
        ++sum;
        if (sum % 5 == 0) printf("\n");
        temp = temp->next;
    }
    printf("\n");
    printf("请输入要添加的楼栋所在的楼盘编号：");
    int id = 0;
    scanf("%d", &id);
    temp = head;
    while (temp->buildings_id != id) {
        temp = temp->next;
    }
    OneBuildingPtr oneBuildingTemp = (OneBuildingPtr) malloc(sizeof(OneBuilding));
    oneBuildingTemp->next = NULL;
    oneBuildingTemp->buildings_id = id;
    printf("已有的楼栋如下：\n");
    OneBuildingPtr nail = temp->head;
    while (nail->next != NULL) {
        printf("编号及楼层数：%d %d", nail->one_building_id, nail->floorCount);
    }
    nail->next = oneBuildingTemp;
    printf("\n");
    /*
    typedef struct OneBuilding {
        int one_building_id;
        int floorCount;
        House *head;
        struct OneBuilding *next;
        int buildings_id;
    } OneBuilding;
     */
    printf("请输入楼栋编号：");
    scanf("%d", &oneBuildingTemp->one_building_id);
    printf("请输入楼栋楼层数：");
    scanf("%d", &oneBuildingTemp->floorCount);
    printf("输入完毕，返回主菜单\n");
}

// 添加房屋
void addRoom(const BuildingsPtr head) {
    int sum = 0;
    printf("已有楼盘数据如下：\n");
    BuildingsPtr temp = head;
    HousePtr house = (HousePtr) malloc(sizeof(House));
    house->next = NULL;
    while (temp != NULL) {
        printf("%d %s\t", temp->buildings_id, temp->name);
        ++sum;
        if (sum % 5 == 0) printf("\n");
        temp = temp->next;
    }
    printf("输入要加入的户型所在的楼盘编号：");
    int id = 0;
    scanf("%d", &id);
    house->buildings_id = id;
    temp = head;
    while (temp != NULL && temp->buildings_id != id) {
        temp = temp->next;
    }
    assert(temp != NULL);
    OneBuildingPtr oneBuilding = temp->head;
    printf("已有楼栋数据如下：\n");
    while (oneBuilding != NULL) {
        printf("楼栋编号及层数：%d %d\n", oneBuilding->one_building_id, oneBuilding->floorCount);
        oneBuilding = oneBuilding->next;
    }
    printf("\n");
    printf("请输入你要添加的户型所在楼栋：");
    scanf("%d", &id);
    house->building_id = id;
    oneBuilding = temp->head;
    while (oneBuilding != NULL && oneBuilding->one_building_id != id) {
        oneBuilding = oneBuilding->next;
    }
    assert(oneBuilding != NULL);
    printf("此楼栋已有的户型信息如下：\n");
    HousePtr houseTemp = oneBuilding->head;
//    typedef struct House {
//        int house_id;
//        char model[100];
//        float area;
//        float prize;
//        struct House *next;
//        int building_id;
//        int buildings_id;
//    } House;
    while (houseTemp != NULL) {
        printf("户型id：%d\n户型：%s\n", houseTemp->house_id, houseTemp->model);
        houseTemp = houseTemp->next;
    }
    printf("\n");
    houseTemp = oneBuilding->head;
    while (houseTemp->next != NULL) {
        houseTemp = houseTemp->next;
    }
    assert(houseTemp != NULL);
    houseTemp->next = house;
    printf("请输入要添加的房屋的id：");
    scanf("%d", &id);
    house->house_id = id;
    sum = 0;
    printf("已有户型：\n");
    for (size_t i = 1; i < sizeof(houseModels) / sizeof(houseModels[0]); ++i) {
        printf("%lu：%s\t", i, houseModels[i]);
        ++sum;
        if (sum % 3 == 0) {
            printf("\n");
        }
    }
    printf("输入要添加的房屋的户型id：");
    scanf("%d", &id);
    strcpy(house->model, houseModels[id]);
    printf("请输入房屋面积：");
    scanf("%f", &house->area);
    printf("请输入房屋价格（万元）：");
    scanf("%f", &house->prize);
    printf("输入完毕，返回主菜单\n");
}

void freeHouse(HousePtr head) {
    free(head);
}

void freeOneBuilding(OneBuildingPtr head) {
    HousePtr temp = head->head;
    while (temp != NULL) {
        HousePtr t = temp;
        temp = t->next;
        freeHouse(t);
    }
    free(head);
}

void freeBuildings(BuildingsPtr head) {
    OneBuildingPtr oneBuildingTemp = head->head;
    while (oneBuildingTemp != NULL) {
        OneBuildingPtr t = oneBuildingTemp;
        oneBuildingTemp = t->next;
        freeOneBuilding(t);
    }
    free(head);
}

// 删除楼盘
void delBuildings(BuildingsPtr *head) {
    BuildingsPtr *temp = head;
    BuildingsPtr buildingsTemp = *head;
    printf("已有楼盘如下：\n");
    int sum = 0;
    while (buildingsTemp != NULL) {
        printf("楼盘编号：%d\n楼盘名称：%s\n\n", buildingsTemp->buildings_id, buildingsTemp->name);
        buildingsTemp = buildingsTemp->next;
        ++sum;
        if (sum % 5 == 0) {
            getchar();
            printf("输入'y'继续输出：");
            if (getchar() == 'y') {
                continue;
            }
            break;
        }
    }
    printf("\n");
    int id = 0;
    printf("输入要删除的楼盘的id：");
    scanf("%d", &id);
    if (id == (*head)->buildings_id) {
        *temp = *head;
        *head = (*head)->next;
        freeBuildings(*head);
        printf("删除完毕，返回主菜单\n");
        return;
    }
    *temp = *head;
    while ((*temp)->next != NULL && (*temp)->next->buildings_id != id) {
        *temp = (*temp)->next;
    }
    buildingsTemp = (*head)->next;
    (*head)->next = buildingsTemp->next;
    freeBuildings(buildingsTemp);
    printf("删除完毕，返回主菜单\n");
}

// 删除楼栋
void delOneBuilding(const BuildingsPtr head) {
    BuildingsPtr temp = head;
    printf("已有楼盘信息如下：\n");
    int sum = 0;
    while (temp != NULL) {
        printf("%d： %s\t", temp->buildings_id, temp->name);
        ++sum;
        if (sum % 5 == 0) {
            getchar();
            printf("输入'y'继续输出：");
            if (getchar() == 'y') {
                continue;
            }
            break;
        }
        temp = temp->next;
    }
    printf("\n请输入你要删除的楼栋所在楼盘编号：");
    int id = 0;
    scanf("%d", &id);
    temp = head;
    while (temp != NULL && temp->buildings_id != id) {
        temp = temp->next;
    }
    assert(temp != NULL);
    printf("此楼盘包含的楼栋信息如下：\n");
    OneBuildingPtr oneBuildingTemp = temp->head;
    while (oneBuildingTemp != NULL) {
        printf("楼栋id：%d\n层数：%d\n\n", oneBuildingTemp->one_building_id, oneBuildingTemp->floorCount);
        oneBuildingTemp = oneBuildingTemp->next;
    }

    printf("请输入你要删除的楼栋的编号：\n");
    scanf("%d", &id);
    oneBuildingTemp = temp->head;
    if (id == oneBuildingTemp->one_building_id) {
        temp->head = oneBuildingTemp->next;
        freeOneBuilding(oneBuildingTemp);
    } else {
        while (oneBuildingTemp->next != NULL && oneBuildingTemp->next->one_building_id != id) {
            oneBuildingTemp = oneBuildingTemp->next;
        }
        OneBuildingPtr t = oneBuildingTemp->next;
        oneBuildingTemp->next = t->next;
        freeOneBuilding(t);
    }
    printf("删除完毕，返回主菜单\n");
}

// 删除房屋
void delRoom(const BuildingsPtr head) {
    BuildingsPtr temp = head;
    printf("已有楼盘信息如下：\n");
    int sum = 0;
    while (temp != NULL) {
        printf("%d： %s\t", temp->buildings_id, temp->name);
        ++sum;
        if (sum % 5 == 0) {
            getchar();
            printf("输入'y'继续输出：");
            if (getchar() == 'y') {
                continue;
            }
            break;
        }
        temp = temp->next;
    }
    printf("\n请输入你要删除的房屋所在楼盘编号：");
    int id = 0;
    scanf("%d", &id);
    temp = head;
    while (temp != NULL && temp->buildings_id != id) {
        temp = temp->next;
    }
    assert(temp != NULL);
    printf("此楼盘包含的楼栋信息如下：\n");
    OneBuildingPtr oneBuildingTemp = temp->head;
    while (oneBuildingTemp != NULL) {
        printf("楼栋id：%d\n层数：%d\n\n", oneBuildingTemp->one_building_id, oneBuildingTemp->floorCount);
        oneBuildingTemp = oneBuildingTemp->next;
    }

    printf("请输入你要删除房屋所在的楼栋的编号：\n");
    scanf("%d", &id);
    oneBuildingTemp = temp->head;
    while (oneBuildingTemp->one_building_id != id) {
        oneBuildingTemp = oneBuildingTemp->next;
    }
    printf("此楼栋包含的房屋类型信息如下：\n");
    HousePtr houseTemp = oneBuildingTemp->head;
//    typedef struct House {
//        int house_id;
//        char model[100];
//        float area;
//        float prize;
//        struct House *next;
//        int building_id;
//        int buildings_id;
//    } House;
    while (houseTemp != NULL) {
        printf("id：%d 类型：%s 面积：%.2f 价格：%.2f\n", houseTemp->house_id, houseTemp->model,
               houseTemp->area, houseTemp->prize);
    }
    printf("请输入你要删除的房子的id：");
    houseTemp = oneBuildingTemp->head;
    scanf("%d", &id);
    if (houseTemp->house_id == id) {
        oneBuildingTemp->head = houseTemp->next;
        freeHouse(houseTemp);
    } else {
        HousePtr t = houseTemp;
        while (houseTemp->next != NULL && houseTemp->house_id != id) {
            houseTemp = houseTemp->next;
        }
        t = houseTemp->next;
        houseTemp->next = t->next;
        freeHouse(t);
    }
    printf("删除完毕，返回主菜单\n");
}

void saveHouse(FILE *file, HousePtr ptr) {
    while (ptr != NULL) {
        fprintf(file, "%d\n", ptr->house_id);
        fprintf(file, "%s\n", ptr->model);
        fprintf(file, "%f\n", ptr->area);
        fprintf(file, "%f\n", ptr->prize);
        fprintf(file, "%d\n", ptr->building_id);
        fprintf(file, "%d\n\n", ptr->buildings_id);
        ptr = ptr->next;
    }

}

void saveOneBuilding(FILE *oneBuilding, FILE *house, OneBuildingPtr ptr) {
    while (ptr != NULL) {
        saveHouse(house, ptr->head);
        fprintf(oneBuilding, "%d\n", ptr->one_building_id);
        fprintf(oneBuilding, "%d\n", ptr->floorCount);
        fprintf(oneBuilding, "%d\n\n", ptr->buildings_id);
        ptr = ptr->next;
    }
}

void saveBuildings(FILE *buildings, FILE *oneBuilding, FILE *house, BuildingsPtr ptr) {
    while (ptr != NULL) {
        saveOneBuilding(oneBuilding, house, ptr->head);
        fprintf(buildings, "%d\n", ptr->buildings_id);
        fprintf(buildings, "%s\n", ptr->name);
        fprintf(buildings, "%d\n", ptr->location_id);
        fprintf(buildings, "%s\n", ptr->location);
        fprintf(buildings, "%s\n\n", ptr->developers);
        ptr = ptr->next;
    }
}

// 保存数据变更的函数
void saveAll(const BuildingsPtr head) {
    FILE *buildings = fopen("buildings.dat", "w");
    FILE *oneBuilding = fopen("oneBuilding.dat", "w");
    FILE *house = fopen("house.dat", "w");
    saveBuildings(buildings, oneBuilding, house, head);
    fclose(buildings);
    fclose(oneBuilding);
    fclose(house);
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
                // 询问是否保存修改的了的数据
                saveAll(*headp);
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
                addBuildings(*headp);
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

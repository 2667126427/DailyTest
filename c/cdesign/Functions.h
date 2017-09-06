//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \|     |// '.
//                 / \|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \  -  /// |     |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
//
//

#ifndef CDESIGN_FUNCTIONS_H
#define CDESIGN_FUNCTIONS_H

// 包含所需头文件
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
#define STATISTIC 10

// 房屋所有户型
const char *const houseModels[] = {"不限", "1室", "2室", "3室", "4室", "5室", "6室及以上"};
// 房屋所在区域
const char *const houseLocations[] = {"不限", "东湖高新区", "洪山区", "江岸区", "东西湖区", "汉阳区", "武昌区", "江汉区"};

int maxHouseId;

// 给c语言加一个bool类型
typedef int bool;
const bool false = 0;
const bool true = 1;
// 前置声明
struct House;
struct OneBuilding;
struct Buildings;

// 房屋的结构体定义
typedef struct House {
    int house_id; // 编号
    char model[100]; // 户型
    float area; // 面积
    float prize; // 价格
    struct House *next; // 指向下一个的指针
    int building_id; // 所在楼栋编号
    int buildings_id; // 所在楼盘编号
} House;
// 指针别名
typedef House *HousePtr;

// 楼栋的结构体定义
typedef struct OneBuilding {
    int one_building_id; // 楼栋编号
    int floorCount; // 楼栋层数
    House *head; // 指向其拥有的房屋的头结点
    struct OneBuilding *next; // 指向同一楼盘下一个楼栋的指针
    int buildings_id; // 所在楼盘编号
} OneBuilding;
// 指针别名
typedef OneBuilding *OneBuildingPtr;

// 楼盘的结构体定义
typedef struct Buildings {
    int buildings_id; // 楼盘定义
    char name[100]; // 楼盘名称
    int location_id; // 所在区域编号
    char location[200]; // 具体位置
    char developers[100]; // 开发商
    OneBuilding *head; // 指向其所有楼栋的指针
    struct Buildings *next; // 只指向下一个楼盘的指针
} Buildings;
// 指针别名
typedef Buildings *BuildingsPtr;

// 清屏函数
void cls() {
    printf("\033c");
}

int cancel() {
    printf("是否取消操作（y/n）：");
    getchar();
    if (getchar() == 'y') {
        cls();
        return 1;
    }
    return 0;
}
// 等待输入返回主菜单
void waitKey() {
    printf("按任意键继续...");
    getchar();
    getchar();
}

// 读取楼盘信息
BuildingsPtr readBuildings(FILE *file, int id) {
    // 分配空间
    BuildingsPtr temp = (BuildingsPtr) malloc(sizeof(Buildings));
    // 空间分配检测
    assert(temp != NULL);
    // 尾指针置为NULL
    temp->next = NULL;
    // 设置编号
    temp->buildings_id = id;
    // 读取相关信息
    fscanf(file, "%s", temp->name);
    fscanf(file, "%d", &temp->location_id);
    fscanf(file, "%s", temp->location);
    fscanf(file, "%s", temp->developers);
    // 返回所分配空间的地址
    return temp;
}

// 读取楼栋信息
OneBuildingPtr readOneBuilding(FILE *file, int id) {
    // 分配空间
    OneBuildingPtr temp = (OneBuildingPtr) malloc(sizeof(OneBuilding));
    // 空间分配失败报错
    assert(temp != NULL);
    // 尾指针置为NULL
    temp->next = NULL;
    // 设置编号
    temp->one_building_id = id;
    // 读取相关信息
    fscanf(file, "%d", &temp->floorCount);
    fscanf(file, "%d", &temp->buildings_id);
//    strtol()
    // 返回所分配的空间
    return temp;
}

// 读取房屋信息
HousePtr readHouse(FILE *file, int id) {
    // 分配空间
    HousePtr temp = (HousePtr) malloc(sizeof(House));
    // 检测分配成功与否
    assert(temp != NULL);
    // 尾指针置空
    temp->next = NULL;
    // 设置编号
    temp->house_id = id;
    if (id > maxHouseId) {
        maxHouseId = id;
    }
    // 读取相关信息
    fscanf(file, "%s", temp->model);
    fscanf(file, "%f", &temp->area);
    fscanf(file, "%f", &temp->prize);
    fscanf(file, "%d", &temp->building_id);
    fscanf(file, "%d", &temp->buildings_id);
    // 返回分配的空间的指针
    return temp;
}

// 判断字符串是否以另一个字符串开头
bool startWith(const char *target, const char *sub) {
    // 首先判断长度关系
    size_t str_len = strlen(target);
    size_t sub_len = strlen(sub);
    if (sub_len > str_len) return false;
    // 然后逐一判断字符
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
    BuildingsPtr buildingsTemp = NULL;
    BuildingsPtr buildingsHead = NULL;
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
        fgetc(buildings);
    }

    // 读入楼栋信息
    OneBuildingPtr oneBuildingTemp = NULL;
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
            }// 否则需要重新寻找对应楼盘
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
                        oneBuildingTemp = oneBuildingTemp->next;
                    }
                    oneBuildingTemp = oneBuildingTemp->next = temp;
                }
            }
        }
        fgetc(oneBuilding);
    }

    // 读取房子信息，与上类似
    HousePtr houseTemp = NULL;
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
        fgetc(house);
    }

    // 关闭文件
    fclose(buildings);
    fclose(oneBuilding);
    fclose(house);
    return buildingsHead;
}

// 释放一个房屋空间
void freeHouse(HousePtr head) {
    free(head);
}

// 释放一个楼栋所在空间
void freeOneBuilding(OneBuildingPtr head) {
    HousePtr temp = head->head;
    // 删除楼栋当然要删除它包含的房屋啦
    while (temp != NULL) {
        // 注意顺序
        HousePtr t = temp;
        temp = t->next;
        freeHouse(t);
    }
    free(head);
}

// 释放一个楼盘所占用空间
void freeBuildings(BuildingsPtr head) {
    OneBuildingPtr oneBuildingTemp = head->head;
    while (oneBuildingTemp != NULL) {
        OneBuildingPtr t = oneBuildingTemp;
        oneBuildingTemp = t->next;
        freeOneBuilding(t);
    }
    free(head);
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
    cls();
    // 设置大一点防止缓冲区溢出
    char choice[1024];
    // 输出提示
    printf("#*************************************************************#\n");
    printf("*           1：查询楼盘    2：查询楼栋    3：查询房屋         *\n");
    printf("*           4：增加楼盘    5：增加楼栋    6：增加户型         *\n");
    printf("*           7：删除楼盘    8：删除楼栋    9：删除户型         *\n");
    printf("*           10：统计房屋信息              0：退出系统         *\n");
    printf("#*************************************************************#\n");
    printf("*                请输入您要进行的操作的编号：[ ]\b\b");
    // 接受输入
    scanf("%s", choice);
    // 判断是否全部是数字
    for (size_t i = 0, len = strlen(choice); i < len; ++i) {
        // 不是数字报错，递归返回
        if (!isdigit(choice[i])) {
            printf("输入错误，请重新输入\n");
            cls();
            return selectChoice();
        }
    }
    // 转换成数字返回
    cls();
    return atoi(choice);
}

// 搜索符合条件的楼盘
int searchBuildings(const BuildingsPtr head) {
    if (cancel())
        return 0;
    // 输入要找的楼盘位置的编号
    printf("输入要找的楼盘所属地区：\n");
    // 输出已有区域供挑选
    for (int i = 0; i < sizeof(houseLocations) / sizeof(houseLocations[0]); ++i) {
        printf("%d：%s\t", i, houseLocations[i]);
        // 换行保持美观
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    int index = 0;
    // 使用字符串数组读取输入
    char temp[1024] = {0};
    scanf("%s", temp);
    // 转换为数字
    index = atoi(temp);
    // 超出范围就报错
    if (index >= sizeof(houseLocations) / sizeof(houseLocations[0]) || index < 0) {
        printf("输入数据超出范围\n");
        return searchBuildings(head);
    }
    // 开始搜索输入区域的楼盘信息
    BuildingsPtr tempPtr = head;
    int sum = 0;
    while (tempPtr != NULL) {
        // 满足区域条件
        if (tempPtr->location_id == index || index == 0) {
            ++sum;
            // 满足条件输出信息
            printf("楼盘编号：%d\n楼盘名称：%s\n地区：%s %s\n开发商：%s\n\n",
                   tempPtr->buildings_id, tempPtr->name, houseLocations[tempPtr->location_id],
                   tempPtr->location, tempPtr->developers);
            // 注意换行
            if (sum % 3 == 0) {
                printf("输入y继续输出，其它字母停止输出：");
                char ch;
                getchar();
                scanf("%c", &ch);
//                printf("get the char: %c\n", ch);
                // 询问是否继续输出
                if (ch != 'y') {
                    break;
                }
            }
        }
        // 向后继续
        tempPtr = tempPtr->next;
    }
    printf("查询完毕，返回主菜单\n");
    waitKey();
    return 0;
}

// 搜索符合条件的楼栋
int searchOneBuilding(const BuildingsPtr head) {
    if (cancel())
        return 0;
    printf("\n");
    // 先打印出所有的区域
    for (size_t i = 0, sum = 0; i < sizeof(houseLocations) / sizeof(houseLocations[0]); ++i) {
        printf("%lu：%s\t", i, houseLocations[i]);
        ++sum;
        if (sum % 3 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    printf("请输入你想要找的区域id：\n");
    printf("\n");
    // 获取区域编号
    int targetRegion;
    scanf("%d", &targetRegion);
    // 楼层高度要求
    printf("请输入您希望的楼层高度区间（例：10 30）：");
    int low = 0, high = 0;
    scanf("%d %d", &low, &high);
    // 开始遍历
    BuildingsPtr temp = head;
    // 变量控制是否继续
    bool isEnd = false;
    int sum = 0;
    while (temp != NULL && !isEnd) {
        OneBuildingPtr oneBuildingTemp = temp->head;
        while (oneBuildingTemp != NULL && !isEnd) {
            //  满足条件就输出
            if ((temp->location_id == targetRegion || targetRegion == 0)
                && oneBuildingTemp->floorCount >= low
                && oneBuildingTemp->floorCount <= high) {
                printf("楼盘id及名称：%d %s\n楼栋id：%d\n楼层高度：%d\n\n", temp->buildings_id, temp->name,
                       oneBuildingTemp->one_building_id, oneBuildingTemp->floorCount);
                ++sum;
                // 询问是否继续输出
                if (sum % 3 == 0) {
                    printf("输入y继续输出，其它字母停止输出：");
                    char ch;
                    getchar();
                    scanf("%c", &ch);
//                    printf("get the char: %c\n", ch);
                    if (ch != 'y') {
                        isEnd = true;
                    }
                }
            }
            // 向后继续
            oneBuildingTemp = oneBuildingTemp->next;
        }
        // 向后继续
        temp = temp->next;
    }
    printf("查询楼栋完毕，返回主菜单\n");
    waitKey();
    return 0;
}

// 搜索符合条件的房屋
// 组合查找
int searchRoom(const BuildingsPtr head) {
    if (cancel())
        return 0;
    printf("已有区域如下：\n");
    for (size_t i = 0, sum = 0; i < sizeof(houseLocations) / sizeof(houseLocations[0]); ++i) {
        printf("%lu：%s\t", i, houseLocations[i]);
        ++sum;
        if (sum % 3 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    printf("输入您希望的房屋所属区域：");
    int location = 0;
    scanf("%d", &location);
    printf("已有户型如下：\n");
    // 输出已有的户型
    for (size_t i = 0; i < sizeof(houseModels) / sizeof(houseModels[0]); ++i) {
        printf("%lu：%s\n", i, houseModels[i]);
    }
    printf("请输入您要查找的户型：\n");
    int target = 0;
    char chs[1024];
    scanf("%s", chs);
    // 户型较少可以直接判断首字符
    if (!isdigit(chs[0])) {
        printf("输入错误请重新输入\n");
        return searchRoom(head);
    }
    target = atoi(chs);
    // 要求输入期望的价格区间
    printf("请输入您希望的价格区间（万元，例：100 150）:");
    int low = 0, high = 0;
    // 读入2个数字
    scanf("%d %d", &low, &high);
    int sum = 0;
    bool isEnd = false;
    BuildingsPtr temp = head;
//    printf("%d\n", target);
    // 开始遍历
    while (temp != NULL && !isEnd) {
        OneBuildingPtr oneBuildingTemp = temp->head;
        while (oneBuildingTemp != NULL && !isEnd) {
            HousePtr houseTemp = oneBuildingTemp->head;
            while (houseTemp != NULL && !isEnd) {
                if ((       // 判断普通户型或者对户型无限制
                            (startWith(houseTemp->model, houseModels[target]) || target == 0)
                            // 室数大于6的判断
                            || (target >= 6 && startWith(houseTemp->model, "6"))
                    )
                    && (temp->location_id == location || location == 0)
                    && houseTemp->prize >= low && houseTemp->prize <= high) {
                    // 满足条件输出信息
                    printf("楼盘名称：%s\n房子编号：%d\n面积及户型：%.2f %s\n价格：%.2f\n地理位置：%s %s\n\n",
                           temp->name, houseTemp->house_id, houseTemp->area, houseTemp->model, houseTemp->prize,
                           houseLocations[temp->location_id], temp->location);
                    ++sum;
                    // 询问是否继续输出
                    if (sum % 3 == 0) {
                        printf("输入y继续输出，其它字母停止输出：");
                        char ch;
                        getchar();
                        scanf("%c", &ch);
//                        printf("get the char: %c\n", ch);
                        if (ch != 'y') {
                            // 不输出把标记设置为true就行了
                            isEnd = true;
                        }
                    }
                }
                houseTemp = houseTemp->next;
            }
            oneBuildingTemp = oneBuildingTemp->next;
        }
        temp = temp->next;
    }
    printf("查询完毕，返回主菜单\n");
    waitKey();
    return 0;

}

// 添加楼盘
int addBuildings(const BuildingsPtr head) {
    if (cancel())
        return 0;
    // 先分配空间
    BuildingsPtr temp = (BuildingsPtr) malloc(sizeof(Buildings));
    assert(temp != NULL);
    temp->next = NULL;
    temp->head = NULL;
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
    // 输入相关信息
//    printf("现有最大编号：%d\n", nail->buildings_id);
//    printf("请输入要加入的楼盘的编号：");
//    scanf("%d", &temp->buildings_id);

    printf("请输入要加入的楼盘的名称：");
    scanf("%s", temp->name);
    printf("请输入要加入的楼盘的所属区域id：\n");
    // 输出所有区域供选择
    for (size_t i = 1, sum = 0; i < sizeof(houseLocations) / sizeof(houseLocations[0]); ++i) {
        printf("%lu：%s\t", i, houseLocations[i]);
        ++sum;
        if (sum % 3 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    int id = 0;
    scanf("%d", &id);
//    scanf("%d", &temp->location_id);
    if (id >= sizeof(houseLocations) / sizeof(houseLocations[0]) || id < 0) {
        printf("输入数据有误，返回主菜单\n");
        freeBuildings(temp);
        return 0;
    }
    temp->location_id = id;
    printf("请输入楼盘具体位置（不要有空格）：");
//    strcpy(temp->location, "嘿呀");
    scanf("%s", temp->location);
    // 空格处理比较麻烦，跳过
    printf("请输入开发商名称（不要有空格）：");
    scanf("%s", temp->developers);
    printf("加入完成，返回主菜单\n");
    BuildingsPtr nail = head;
    // 找到最后一个节点
    while (nail->next != NULL)nail = nail->next;
    nail->next = temp;
    temp->buildings_id = nail->buildings_id + 1;
    waitKey();
    return 0;
}

// 添加楼栋
int addOneBuilding(const BuildingsPtr head) {
    if (cancel())
        return 0;
    // 输出已有楼盘数据
    printf("已有楼盘数据如下：\n");
    BuildingsPtr temp = head;
    int sum = 0;
    while (temp != NULL) {
        printf("编号及名称位置：%02d %-30s %-10s\n", temp->buildings_id, temp->name,
               houseLocations[temp->location_id]);
        ++sum;
        // 输出处理
        if (sum % 5 == 0) {
            printf("输入y继续输出，其它字母停止输出：");
            char ch;
            getchar();
            scanf("%c", &ch);
//            printf("get the char: %c\n", ch);
            if (ch != 'y') {
                // 不输出把标记设置为true就行了
                break;
            }
        }
        temp = temp->next;
    }
    printf("\n");
//    if (cancel())
//        return 0;
    // 询问楼盘编号
    printf("请输入要添加的楼栋所在的楼盘编号：");
    int id = 0;
    scanf("%d", &id);
    temp = head;
    // 找到那个楼盘
    while (temp != NULL && temp->buildings_id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("输入数据有误，加入失败，返回主菜单\n");
        waitKey();
        return 0;
    }
    // 分配空间
    OneBuildingPtr oneBuildingTemp = (OneBuildingPtr) malloc(sizeof(OneBuilding));
    oneBuildingTemp->next = NULL;
    oneBuildingTemp->head = NULL;
    oneBuildingTemp->buildings_id = id;
    // 输出已有楼栋，很有可能是空的。。。
//    printf("已有的楼栋如下：\n");
//    printf("\n");
//    if (cancel()) {
//        freeOneBuilding(oneBuildingTemp);
//        return 0;
//    }
    /*
    typedef struct OneBuilding {
        int one_building_id;
        int floorCount;
        House *head;
        struct OneBuilding *next;
        int buildings_id;
    } OneBuilding;
     */
    // 读取相关信息
//    printf("请输入楼栋编号：");
//    scanf("%d", &oneBuildingTemp->one_building_id);


    printf("请输入楼栋楼层数：");
    scanf("%d", &oneBuildingTemp->floorCount);
    if (oneBuildingTemp->floorCount <= 0) {
        printf("输入数据有误， 返回主菜单\n");
        freeOneBuilding(oneBuildingTemp);
        waitKey();
    }
    printf("输入完毕，返回主菜单\n");
    OneBuildingPtr nail = temp->head;
    if (nail == NULL) {
        temp->head = oneBuildingTemp;
        oneBuildingTemp->one_building_id = 1;
    } else {
        while (nail->next != NULL) {
//            printf("编号及楼层数：%d %d\n", nail->one_building_id, nail->floorCount);
            nail = nail->next;
        }
//        printf("编号及楼层数：%d %d\n", nail->one_building_id, nail->floorCount);
        nail->next = oneBuildingTemp;
        oneBuildingTemp->one_building_id = nail->one_building_id + 1;
    }
    waitKey();
    return 0;
}

// 添加房屋
int addRoom(const BuildingsPtr head) {
    int sum = 0;
    // 输出已有楼盘数据
    printf("已有楼盘数据如下：\n");
    BuildingsPtr temp = head;
    // 分配空间
    HousePtr house = (HousePtr) malloc(sizeof(House));
    house->next = NULL;
    while (temp != NULL) {
        printf("%02d %-20s %s\t", temp->buildings_id, houseLocations[temp->location_id], temp->name);
        ++sum;
        if (sum % 3 == 0)
            printf("\n");
        temp = temp->next;
    }
    printf("\n");
    if (cancel()) {
        freeHouse(house);
        return 0;
    }
    printf("输入要加入的户型所在的楼盘编号：");
    int id = 0;
    scanf("%d", &id);
    house->buildings_id = id;
    temp = head;
    while (temp != NULL && temp->buildings_id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("输入数据有误，加入失败，返回主菜单\n");
        freeHouse(house);
        waitKey();
        return 0;
    }
//    assert(temp != NULL);
    OneBuildingPtr oneBuilding = temp->head;
    // 输出已有楼栋数据
    printf("已有楼栋数据如下：\n");
    while (oneBuilding != NULL) {
        printf("楼栋编号及层数：%d %d\n", oneBuilding->one_building_id, oneBuilding->floorCount);
        oneBuilding = oneBuilding->next;
    }
    printf("\n");
    if (cancel()) {
        freeHouse(house);
        return 0;
    }
    // 询问楼栋
    printf("请输入你要添加的户型所在楼栋：");
    scanf("%d", &id);
    house->building_id = id;
    oneBuilding = temp->head;
    while (oneBuilding != NULL && oneBuilding->one_building_id != id) {
        oneBuilding = oneBuilding->next;
    }
    if (oneBuilding == NULL) {
        printf("输入数据有误，加入失败，返回主菜单\n");
        freeHouse(house);
        waitKey();
        return 0;
    }
//    assert(oneBuilding != NULL);
//    printf("此楼栋已有的房屋信息如下：\n");
    HousePtr houseTemp;
    // 输出已有房屋
//    while (houseTemp != NULL) {
//        printf("房屋编号：%d\n户型：%s\n", houseTemp->house_id, houseTemp->model);
//        houseTemp = houseTemp->next;
//    }
//    printf("\n");
    houseTemp = oneBuilding->head;
    if (houseTemp == NULL) {
        oneBuilding->head = house;

    } else {
        while (houseTemp->next != NULL) {
            houseTemp = houseTemp->next;
        }
        houseTemp->next = house;
    }
    assert(houseTemp != NULL);
    house->house_id = ++maxHouseId;
    // 开始读入数据
//    printf("请输入要添加的房屋的id：");
//    scanf("%d", &id);
//    house->house_id = id;
//    sum = 0;
    // 显示已有户型
//    printf("已有户型：\n");
//    for (size_t i = 1; i < sizeof(houseModels) / sizeof(houseModels[0]); ++i) {
//        printf("%lu：%s\t", i, houseModels[i]);
//        ++sum;
//        if (sum % 3 == 0) {
//            printf("\n");
//        }
//    }
    // 读入数据
    printf("输入要添加的房屋的户型（例：2室1厅1卫）：");
    scanf("%s", house->model);
//    strcpy(house->model, houseModels[id]);
    printf("请输入房屋面积：");
    scanf("%f", &house->area);
    printf("请输入房屋价格（万元）：");
    scanf("%f", &house->prize);
    printf("输入完毕，返回主菜单\n");
    waitKey();
    return 0;
}

// 删除一个楼盘
void delBuildings(BuildingsPtr *head) {
    BuildingsPtr temp;
    BuildingsPtr buildingsTemp = *head;
    // 先把已有的信息输出
    printf("已有楼盘如下：\n");
    int sum = 0;
    while (buildingsTemp != NULL) {
        printf("楼盘编号及地域：%d %s\n楼盘名称：%s\n\n", buildingsTemp->buildings_id,
               houseLocations[buildingsTemp->location_id], buildingsTemp->name);
        buildingsTemp = buildingsTemp->next;
        ++sum;
        if (sum % 5 == 0) {
            getchar();
            // 询问是否继续输出
            printf("输入'y'继续输出：");
            if (getchar() != 'y') {
                break;
            }
        }
    }
    printf("\n");
    int id = 0;
    // 获取要删除的楼盘编号
    printf("输入要删除的楼盘的编号：");
    scanf("%d", &id);
    // 如果要删除的是第一个
    if (id == (*head)->buildings_id) {
        // 顺序比较重要
        temp = *head;
        *head = (*head)->next;
        freeBuildings(temp);
        printf("删除完毕，返回主菜单\n");
        waitKey();
        return;
    }
    // 删除的不是第一个就往下面找吧
    temp = *head;
    while (temp->next != NULL && temp->next->buildings_id != id) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("输入数据有误，返回主菜单\n");
        waitKey();
        return;
    }
    // 对应删除股即可
    buildingsTemp = temp->next;
    temp->next = buildingsTemp->next;
    freeBuildings(buildingsTemp);
    printf("删除完毕，返回主菜单\n");
    waitKey();
}

// 删除一个楼栋
void delOneBuilding(const BuildingsPtr head) {
    BuildingsPtr temp = head;
    // 首先输出已有信息
    printf("已有楼盘信息如下：\n");
    int sum = 0;
    while (temp != NULL) {
        printf("%d： %s\t", temp->buildings_id, temp->name);
        ++sum;
        if (sum % 5 == 0) {
            printf("\n");
            getchar();
            // 询问是否继续输出
            printf("输入'y'继续输出：");
            if (getchar() != 'y') {
                break;
            }
        }
        // 向下迭代
        temp = temp->next;
    }
    // 询问编号
    printf("\n请输入你要删除的楼栋所在楼盘编号：");
    int id = 0;
    scanf("%d", &id);
    temp = head;
    // 找到对应编号的楼盘
    while (temp != NULL && temp->buildings_id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("输入数据有误，返回主菜单\n");
        waitKey();
        return;
    }
    assert(temp != NULL);
    // 输出楼盘所包含的楼栋信息
    printf("此楼盘包含的楼栋信息如下：\n");
    OneBuildingPtr oneBuildingTemp = temp->head;
    while (oneBuildingTemp != NULL) {
        printf("楼栋id：%d\n层数：%d\n\n", oneBuildingTemp->one_building_id, oneBuildingTemp->floorCount);
        oneBuildingTemp = oneBuildingTemp->next;
    }
    if (cancel()) {
        return;
    }
    // 得到楼栋编号
    printf("请输入你要删除的楼栋的编号：");
    scanf("%d", &id);
    oneBuildingTemp = temp->head;
    // 如果是第一个就特殊处理一下
    if (id == oneBuildingTemp->one_building_id) {
        temp->head = oneBuildingTemp->next;
        freeOneBuilding(oneBuildingTemp);
    } else {
        // 找到对应的楼栋
        while (oneBuildingTemp->next != NULL && oneBuildingTemp->next->one_building_id != id) {
            oneBuildingTemp = oneBuildingTemp->next;
        }
        if (oneBuildingTemp->next == NULL) {
            printf("输入数据有误，返回主菜单\n");
            waitKey();
            return;
        }
        OneBuildingPtr t = oneBuildingTemp->next;
        oneBuildingTemp->next = t->next;
        freeOneBuilding(t);
    }
    printf("删除完毕，返回主菜单\n");
    waitKey();
}

// 删除一个房屋
void delRoom(const BuildingsPtr head) {
    BuildingsPtr temp = head;
    // 输出已有的楼盘信息
    printf("已有楼盘信息如下：\n");
    int sum = 0;
    while (temp != NULL) {
        printf("%d： %s\t", temp->buildings_id, temp->name);
        ++sum;
        if (sum % 3 == 0) {
            printf("\n");
            getchar();
            printf("输入'y'继续输出：");
            if (getchar() != 'y') {
                break;
            }
        }
        temp = temp->next;
    }
    // 得到要删除的房屋所在楼盘编号
    printf("\n请输入你要删除的房屋所在楼盘编号：");
    int id = 0;
    scanf("%d", &id);
    temp = head;
    while (temp != NULL && temp->buildings_id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("输入数据有误，返回主菜单\n");
        waitKey();
        return;
    }
    assert(temp != NULL);
    // 获取所在楼栋编号
    printf("此楼盘包含的楼栋信息如下：\n");
    OneBuildingPtr oneBuildingTemp = temp->head;
    while (oneBuildingTemp != NULL) {
        printf("楼栋id：%d\n层数：%d\n\n", oneBuildingTemp->one_building_id, oneBuildingTemp->floorCount);
        oneBuildingTemp = oneBuildingTemp->next;
    }

    printf("请输入你要删除房屋所在的楼栋的编号：");
    scanf("%d", &id);
    oneBuildingTemp = temp->head;
    while (oneBuildingTemp != NULL && oneBuildingTemp->one_building_id != id) {
        oneBuildingTemp = oneBuildingTemp->next;
    }
    if (oneBuildingTemp == NULL) {
        printf("输入数据有误，返回主菜单\n");
        return;
    }
    // 输出已有的信息
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
        houseTemp = houseTemp->next;
    }
    if (cancel()) {
        return;
    }
    // 进行删除
    printf("请输入你要删除的房子的id：");
    houseTemp = oneBuildingTemp->head;

    scanf("%d", &id);
    if (houseTemp == NULL) {
        printf("输入数据有误，返回主菜单\n");
        waitKey();
        return;
    }
    // 第一个特殊处理
    if (houseTemp->house_id == id) {
        oneBuildingTemp->head = houseTemp->next;
        freeHouse(houseTemp);
    } else {
        // 其他的类似
//        HousePtr t;
        while (houseTemp->next != NULL && houseTemp->house_id != id) {
            houseTemp = houseTemp->next;
        }
        if (houseTemp->next == NULL) {
            printf("输入数据有误，返回主菜单\n");
            waitKey();
            return;
        }
        HousePtr t = houseTemp->next;
        houseTemp->next = t->next;
        freeHouse(t);
    }
    printf("删除完毕，返回主菜单\n");
    waitKey();
}

// 数据持久化
void saveHouse(FILE *file, HousePtr ptr) {
    // 写入到文件里
    while (ptr != NULL) {
        fprintf(file, "%d\n", ptr->house_id);
        fprintf(file, "%s\n", ptr->model);
        fprintf(file, "%.2f\n", ptr->area);
        fprintf(file, "%.2f\n", ptr->prize);
        fprintf(file, "%d\n", ptr->building_id);
        fprintf(file, "%d\n\n", ptr->buildings_id);
        ptr = ptr->next;
    }
}

// 数据持久化
void saveOneBuilding(FILE *oneBuilding, FILE *house, OneBuildingPtr ptr) {
    // 写入到文档中去
    while (ptr != NULL) {
        // 保存房屋信息
        saveHouse(house, ptr->head);
        fprintf(oneBuilding, "%d\n", ptr->one_building_id);
        fprintf(oneBuilding, "%d\n", ptr->floorCount);
        fprintf(oneBuilding, "%d\n\n", ptr->buildings_id);
        ptr = ptr->next;
    }
}

// 数据持久化
void saveBuildings(FILE *buildings, FILE *oneBuilding, FILE *house, BuildingsPtr ptr) {
    // 保存数据
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
    // 询问是否保存数据
    printf("是否保存已修改的数据（y/n）：");
    getchar();
    if (getchar() != 'y') {
        return;
    }
    FILE *buildings = fopen("buildings.dat", "w");
    FILE *oneBuilding = fopen("oneBuilding.dat", "w");
    FILE *house = fopen("house.dat", "w");
    saveBuildings(buildings, oneBuilding, house, head);
    fclose(buildings);
    fclose(oneBuilding);
    fclose(house);
}

// 统计数据
void statistic(BuildingsPtr head) {
    int regions[7] = {0};
    int models[5] = {0};
    /*0 0~49
     * 1 50~99
     * 2 100~149
     * 3 150~199
     * 4 200~249
     * 5 250~299
     * 6 300~349
     * 7 350~399
     * 8 400~449
     * 9 450~499
     * 10 500~...
     * */
    int prices[11] = {0};
    BuildingsPtr buildingsTemp = head;
    while (buildingsTemp != NULL) {
        OneBuildingPtr oneBuildingTemp = buildingsTemp->head;
        while (oneBuildingTemp != NULL) {
            HousePtr houseTemp = oneBuildingTemp->head;
            while (houseTemp != NULL) {
                ++regions[buildingsTemp->location_id - 1];
                ++models[houseTemp->model[0] - '1'];
//                printf("%.2f\n", houseTemp->prize);
                int t = (int) houseTemp->prize;
                if (t / 50 <= 9) {
                    ++prices[t / 50];
                } else {
                    ++prices[10];
                }
                houseTemp = houseTemp->next;
            }
            oneBuildingTemp = oneBuildingTemp->next;
        }
        buildingsTemp = buildingsTemp->next;
    }
    // 统计完毕，进行输出

    // 首先输出地域分布
    for (size_t i = 0; i < sizeof(houseLocations) / sizeof(houseLocations[0]) - 1; ++i) {
        printf("地区：%-20s房屋类型数：%d\n", houseLocations[i + 1], regions[i]);
    }
    printf("\n");
    // 输出房屋类型分布
    for (int i = 0; i < sizeof(models) / sizeof(models[0]); ++i) {
        printf("%d室：共%02d处\n", i + 1, models[i]);
    }
    printf("\n");
    // 输出价格区间的分布
    for (int i = 0; i < sizeof(prices) / sizeof(prices[0]); ++i) {
        printf("%03d~%03d（万元）：共%d处\n", i * 50, i * 50 + 49, prices[i]);
    }
    printf("\n");
    printf("输出完毕，返回主菜单\n");
    waitKey();
}

// 提供操作
void operations(BuildingsPtr *headp) {
    int choice = 0;
    // 设置结束的标记
    bool isEnd = false;
    while (!isEnd) {
        cls();
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
            case STATISTIC:
                // 统计楼盘相关信息
                statistic(*headp);
                break;
            default:
                // 调到这里说明输入数字不在上面的操作中，给予提示
                printf("无此选项，请重新输入");
                waitKey();
        }
    }
}

#endif //CDESIGN_FUNCTIONS_H

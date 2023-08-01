#include"public.h"
#include"test.pb.h"
#include"./taskMemory.h"
#include"./jsoncpp/json.h"
using namespace std;
char buf[124];
string data;
void ReadMemory();
void WriteMemory();
void testJsonCpp();
void setSeriestoFd();
void getSeriestoFd();
void setSeriestoArray();
void setSeriestoString();
void getSeriesFromArray();
void getSeriesFromString();
void setSeriestoStream();
void getSeriestoFStream();
void testShareMemory(int num);

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    setSeriestoArray();
    getSeriesFromArray();
    setSeriestoString();
    getSeriesFromString();
    testJsonCpp();
    
    //test sharememory
    int nNum;
    cin >> nNum;
    testShareMemory(nNum);
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}

void setSeriestoArray()
{
    test::student studenA;
    studenA.set_name("xiaoming");
    studenA.set_age(11);
    int len = studenA.ByteSizeLong();
    studenA.SerializeToArray(buf, len);
    printf("setSeries data: %s\n", buf);
}

void getSeriesFromArray()
{
    test::student studenA;
    int nLen = strlen(buf);
    studenA.ParseFromArray(buf, nLen);
    string name = studenA.name();
    int age = studenA.age();
    printf("getSeries data name: %s age: %d\n", name.c_str(), age);
}

void setSeriestoString()
{
    test::student studenA;
    studenA.set_name("xiaoming");
    studenA.set_age(11);
    studenA.SerializeToString(&data);
    printf("setSeriestoString data: %s\n", data.c_str());
}

void getSeriesFromString()
{
    test::student studenA;
    studenA.ParseFromString(data);
    string name = studenA.name();
    int age = studenA.age();
    printf("getSeriesFromString data name: %s age: %d\n", name.c_str(), age);
}

void setSeriestoStream()
{
    test::student studenA;
    fstream outStr("./test.txt", ios::out|ios::trunc|ios::binary);
    outStr << "helloworld";
    studenA.SerializeToOstream(&outStr);
    outStr.close();
}

void getSeriestoFStream()
{
    test::student studenA;
    fstream inStr("./test.txt", ios::in);
    studenA.ParseFromIstream(&inStr);
    inStr.close();
}

void setSeriestoFd()
{
    test::student studenA;
    studenA.set_age(12);
    studenA.set_name("xiaoming");
    int fd = open("./test1.txt", O_CREAT|O_WRONLY|O_TRUNC);
    if (fd < 0)
    {
        printf("setSeriestoFd open error\n");
    }
    
    studenA.SerializeToFileDescriptor(fd);
}

void getSeriestoFd()
{
    test::student studenA;
    int fd = open("./test1.txt",O_RDONLY);
    if (fd < 0)
    {
        printf("getSeriestoFd open error\n");
    }
    
    studenA.ParseFromFileDescriptor(fd);
}

void testJsonCpp()
{
    string message = "{ \"data\" : { \"username\" : \"test\" }, \"type\" : 6 }";
    Json::Reader reader(Json::Features::strictMode());
    Json::Value parseData;
    if (reader.parse(message.c_str(), parseData))
    {
        int type = parseData.get("type", 0).asInt();
        Json::Value frameData = parseData.get("data", 0);
        string username = frameData.get("username", 0).asString();
        printf("type: %d, username: %s\n", type, username.c_str());
    }
 
    // 生成json串
    Json::Value newdata;
    Json::Value frame;
    Json::FastWriter fastWriter;
 
    frame["type"] = 66;
    newdata["username"] = "test";
    frame["data"] = newdata;
 
    string result = fastWriter.write(frame);
    printf("result: %s \n", result.c_str());
}

void testShareMemory(int num)
{
    printf("num value: %d\n", num);
   switch(num)
   {
        case 1:
        {
            WriteMemory();
            break;
        }
        
        case 2:
        {
            ReadMemory();
            break;
        }
        
        default:
        {
            printf("testShareMemory other cases\n");
        }
   }
}

void WriteMemory()
{
    string path = "/home";
    privatedata testData;
    privateMemory personData(path, 10);
    testData.age = 11;
    testData.key = "testKey";
    testData.scores = 37;
    testData.userInfo = "student";
    sprintf(testData.id, "123456");
    personData.shyWrite(&testData);
    printf("WriteMemory other cases\n");
}

void ReadMemory()
{
    string path = "/home";
    privatedata testData;
    char clientId[10] = "123456";
    char key[10] = "testKey";
    privateMemory personData(path, 10);
    privatedata retData = personData.shyRead(clientId, key);
    printf("ReadMemory userInfo: %s key: %s id: %s age: %d scores: %d\n",
        retData.userInfo.c_str(), retData.key.c_str(), retData.id, retData.age, retData.scores);
}
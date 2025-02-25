#include <bits/stdc++.h>
using namespace std;

class User {         //用户类
    public:
        string username;
        string role;
        double balance;

        User(const string& username, const string& password, const string& role, double balance = 0)
        :username(username), role(role), balance(balance) {
            set_password(password);
        }

        string get_password() const {
            return password;
        }

        void set_password(const string& new_password) {
            password = new_password;
        }
        
    private:
        string password;
};

class Room {         //房间类
    public:
        int room_number;
        string room_type;
        double price;
        bool isempty;

        Room(int room_number, const string& room_type, double price, bool isempty = true)
        :room_number(room_number), room_type(room_type),  price(price), isempty(isempty) {}
};

class User_Manage {     //用户管理类
    private:
        vector<User> users;

        void load_users_from_file() {        //加载用户数据
            ifstream file("users.txt");
            string line;
            while (getline(file,line)) {
                stringstream ss(line);
                string username,password,role;
                double balance;
                getline(ss,username,',');
                getline(ss,password,',');
                getline(ss,role,',');
                ss >> balance;
                users.emplace_back(username,password,role,balance);
            }
            file.close();
        }

        void save_users_to_file() const {     //保存到文件
            ofstream file("users.txt");
            for ( const auto& user : users ) {
                file << user.username << "," << user.get_password() << "," << user.role << "," << user.balance << endl;
            }
            file.close();
        }
    
    public:
        User_Manage() {
            load_users_from_file();
        }
        ~User_Manage() {
            save_users_to_file();
        }

        void add_user ( const User& user ) {  //添加用户
            users.push_back(user);
            save_users_to_file();
        }

        void delete_user( const string& username ) {  //删除用户
            for( auto it = users.begin(); it != users.end(); it++ ) {
                if ( it->username == username ) {
                    users.erase(it);
                    save_users_to_file();
                    return;
                }
            }
        }

        void update_user ( const User& user ) {    //更新用户信息
            for ( auto& u : users ) {
                if ( u.username == user.username ) {
                    u.set_password(user.get_password());
                    u.role = user.role;
                    u.balance = user.balance;
                    save_users_to_file();
                    return;
                }
            }
        }

        User* find_user ( const string& username) {     //查找用户
            for ( auto& u : users ) {
                if ( u.username == username ) {
                    return &u;
                }
            }
            return nullptr;
        }

        const vector<User>& get_users() const {
            return users;
        }
};

class Room_Manage {
    private:
        vector<Room> rooms;
        void load_room_from_file() {             //加载房间信息
            ifstream file("room.txt");
            string line;
            while ( getline(file,line) ) {
                stringstream ss(line);
                int room_number;
                string room_type;
                double price;
                bool isempty;
                ss >> room_number;
                ss.ignore();
                getline(ss,room_type,',');
                ss >> price;
                ss.ignore();
                ss >> isempty;
                rooms.emplace_back(room_number, room_type, price, isempty);
            }
            file.close();
        }

        void save_rooms_to_file() const {      //保存到文件
            ofstream file("rooms.txt");
            for ( const auto& room : rooms ) {
                file << room.room_number << "," << room.room_type << "," << room.price << "," << room.isempty << endl;
            }
            file.close();
        }

    public:
        Room_Manage() {
            load_room_from_file();
        }
        ~Room_Manage() {
            save_rooms_to_file();
        }

        void delete_room( int room_number ) {       //删除房间
            for ( auto it = rooms.begin(); it != rooms.end(); it++ ) {
                if ( it->room_number == room_number ) {
                    rooms.erase(it);
                    save_rooms_to_file();
                    return;
                }
            }
        }

        void update_room( const Room& room ) {    //更新房间信息
            for ( auto& r : rooms ) {
                if ( r.room_number == room.room_number ) {
                    r.room_type = room.room_type;
                    r.price = room.price;
                    r.isempty = room.isempty;
                    save_rooms_to_file();
                    return;
                }
            }
        }
        
        Room* find_room( int room_number ) {     //查找房间
            for ( auto& r : rooms ) {
                if ( r.room_number == room_number ) {
                    return &r;
                } 
            }
            return nullptr;
        }

        const vector<Room>& get_rooms() const {
            return rooms;
        }

        int get_empty_room( const string& room_type ) const {      //获取空房间数量
            int cnt = 0;
            for ( const auto& room : rooms ) {
                if ( room.room_type == room_type && room.isempty ) {
                    cnt++;
                }
            }
            return cnt;
        }
};

class Hotel_Manage {     //酒店管理类
    private:
        User_Manage user_manage;
        Room_Manage room_manage;
    public:
        Hotel_Manage() {
            User admin("admin", "admin123", "admin");           //预设管理员账号
            if ( user_manage.find_user(admin.username) == nullptr ) {
                user_manage.add_user(admin);
            }
        }

        void add_user() {          //添加用户
            string username, password, role;
            double balance = 0;
            cout << "请输入用户名：";
            cin >> username;
            cout << "请输入密码：";
            cin >> password;
            cout << "请输入角色(admin/customer/member)";
            cin >> role;
            if ( role == "member" ) {
                cout << "请输入会员余额：";
                cin >> balance;
            }
            user_manage.add_user(User(username,password,role,balance));
        }

        void delete_user() {         //删除用户
            string username;
            cout << "请输入要删除的用户名：";
            cin >> username;
            user_manage.delete_user(username);
        }

        void update_user() {         //更新用户信息
            string username,password,role;
            double balance = 0;
            cout << "请输入要更新的用户名：";
            cin >> username;
            User* user = user_manage.find_user(username);
            if ( user ) {
                cout << "请输入新密码：";
                cin.ignore();
                getline(cin,password);
                if ( !password.empty() ) {
                    user->set_password(password);
                }
                cout << "请输入新角色：";
                getline(cin,role);
                if ( !role.empty() ) {
                    user->role = role;
                }
                if ( role == "member" ) {
                    cout << "请输入新会员余额：";
                    string input;
                    getline(cin,input);
                    if ( !input.empty() ) {
                        stringstream ss(input);
                        ss >> balance;
                        user->balance = balance;
                    }
                }
                user_manage.update_user(*user);
            }else {
                cout << "用户不存在" << endl;
            }
        }

        void add_room() {     //添加房间
            string username;
            cout << "请输入管理员用户名：";
            cin >> username;
            if ( user_manage.find_user(username) && user_manage.find_user(username)->role == "admin" ) {
                int room_number;
                string room_type;
                double price;
                cout << "请输入房间号：";
                cin >> room_number;
                cout << "请输入房间类型：";
                cin.ignore();
                getline(cin,room_type);
                cout << "请输入房间价格：";
                cin >> price;
                room_manage.update_room(Room(room_number,room_type,price));
            }else {
                cout << "您没有权限" << endl;
            }
        }

        void delete_room() {   //删除房间
            string username;
            cout << "请输入管理员用户名：";
            cin >> username;
            if ( user_manage.find_user(username) && user_manage.find_user(username)->role == "admin" ) {
                int room_number;
                cout << "请输入要删除的房间号：";
                cin >> room_number;
                room_manage.delete_room(room_number);
            }else {
                cout << "您没有权限" << endl;
            }
        }

        void update_room() {            //更新房间信息
            string username;
            cout << "请输入管理员用户名：";
            cin >> username; 
            if ( user_manage.find_user(username) && user_manage.find_user(username)->role == "admin" ) {
                int room_number;
                string room_type;
                double price;
                bool isempty;
                cout << "请输入要更新的房间号：";
                cin >> room_number;
                Room* room = room_manage.find_room(room_number);
                if ( room ) {
                    cout << "请输入房间类型：";
                    cin.ignore();
                    getline(cin,room_type);
                    if ( !room_type.empty() ) {
                        room->room_type = room_type;
                    }
                    cout << "请输入房间新价格：";
                    string input;
                    getline(cin,input);
                    if ( !input.empty() ) {
                        stringstream ss(input);
                        ss >> price;
                        room->price = price;
                    }
                    cout << "请输入新房间状态( 1 : 可用 ， 0 : 不可用)：" ;
                    getline(cin,input);
                    if ( !input.empty() ) {
                        stringstream ss(input);
                        ss >> isempty;
                        room->isempty = isempty;
                    }
                    room_manage.update_room(*room);
                }else {
                    cout << "房间不存在：" << endl;
                }
            }else {
                cout << "您没有权限" << endl;
            }
        }

        void book_room() {       //预订房间
            string username;
            cout << "请输入用户名：";
            cin >> username;
            User* user = user_manage.find_user(username);
            if ( user && (user->role == "customer" || user->role == "member") ) {
                int room_number;
                cout << "请输入要预订的房间号：";
                cin >> room_number;
                Room* room = room_manage.find_room(room_number);
                if ( room && room->isempty ) {
                        if ( user->balance >= room->price ) {
                            user->balance -= room->price;
                            room->isempty = false;
                            user_manage.update_user(*user);
                            room_manage.update_room(*room);
                            cout << "预订成功" << endl;
                        }else {
                            cout << "余额不足" << endl;
                        }                  
                }else {
                    cout << "房间不可用或不存在" << endl;
                }
            }else {
                cout << "用户不存在或没有权限" << endl;
            }
        }

        void query_room() {          //查询房间
            const auto& rooms = room_manage.get_rooms();
            cout << "房间列表：" << endl;
            cout << "房间号\t房间类型\t价格\t是否可用" << endl;
            for ( const auto& room : rooms ) {
                cout << room.room_number << "\t" << room.room_type << "\t" << room.price << "\t" << (room.isempty ? "是" : "否") << endl; 
            }
        }

        void run() {
            int choice;
            while ( true ) {
                cout << "\n酒店管理系统" << endl;
                cout << "1.添加用户" << endl;
                cout << "2.删除用户" << endl;
                cout << "3.更新用户" << endl;
                cout << "4.添加房间" << endl;
                cout << "5.删除房间" << endl;
                cout << "6.更新房间" << endl;
                cout << "7.预订房间" << endl;
                cout << "8.退出房间" << endl;
                cout << "9.推出" << endl;
                cout << "请选择操作：";
                cin >> choice;
                switch ( choice ) {
                    case 1:
                        add_user();
                        break;
                    case 2:
                        delete_user();
                        break;
                    case 3:
                        update_user();
                        break;
                    case 4:
                        add_room();
                        break;
                    case 5:
                        delete_room();
                        break;
                    case 6:
                        update_room ();
                        break;
                    case 7:
                        book_room();
                        break;
                    case 8:
                        query_room();
                        break;
                    case 9:
                        return;
                    default:
                        cout << "无效选择，请重新输入" << endl;
                }
            }
        }
};

int main ( )
{
    Hotel_Manage system;
    system.run();
    return 0;
}
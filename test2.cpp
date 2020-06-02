//課題8 detector[3]について
#include<bits/stdc++.h>
#define _GLIBCXX_DEBUG
using namespace std;
using ld =long double;

class x_ray_vector{
private:
public:

    pair<ld,ld> para;
    pair<ld,ld> cons;//v=cons+a*para 
    x_ray_vector(pair<ld,ld>p,pair<ld,ld>c){
        para=p;
        cons=c;
    }
    pair<ld,ld> x_axis_to_point(ld x_axis){//cons.first+a*para.first=x_axis
        ld a=(x_axis-cons.first)/para.first;//ベクトルをa分のばす
        pair<ld,ld>res=make_pair(x_axis,cons.second+a*para.second);
        return res;
    }
    pair<ld,ld> y_axis_to_point(ld y_axis){//cons.second+a*para.second=y_axis
        ld a=(y_axis-cons.second)/para.second;//ベクトルをa分のばす
        pair<ld,ld>res=make_pair(cons.first+a*para.first,y_axis);
        return res;
    }
};
class grid{
    private:
       
        ld mono_length;//単位グリッドの一辺の長さ
        
    public:
        vector<ld> x_axis_s;
        vector<ld> y_axis_s;
        vector<vector<ld>> v;
        int n;
        ld length;
        vector<vector<ld>>grid_weight;
        grid(int split_number,ld node_length,vector<vector<ld>>weight){//分割数n*nと正方形の一辺の長さ
            n=split_number;
            length=node_length;
            mono_length=length/(ld)n;
            grid_weight.resize(n);
            for(int i=0;i<n;i++){
                grid_weight[i].resize(n);
                for(int j=0;j<n;j++){
                    grid_weight[i][j]=weight[i][j];
                }
            }
            v.resize(split_number);
            for(int i=0;i<split_number;i++){
                v[i].resize(split_number);
            }
            /*
            for(int i=0;i<split_number;i++){
                for(int j=0;j<split_number;j++){
                    v[i][j]=0;
                }
            }
            */
            //x_axis_s
            x_axis_s.resize(n+1);
            for(int i=0;i<=n;i++){
                x_axis_s[i]=-(length/2)+i*mono_length;
            }
            y_axis_s.resize(n+1);
            for(int j=0;j<=n;j++){
                y_axis_s[j]=-(length/2)+j*mono_length;
            }

        }
        ld fragment_length(pair<ld,ld>p1,pair<ld,ld>p2){//与えられた線分の長さを計算する
            ld mono_grid_length=hypot(p1.first-p2.first,p1.second-p2.second);
            pair<ld,ld>center=make_pair((p1.first+p2.first)/2,(p1.second+p2.second)/2);
            //まず、何行目かを特定する
            //左上の頂点(-l/2,l/2)を(0,0)と考える   
            ld new_y=center.second-length/2;
            ld new_y_abs_len=abs(new_y);
            //以下、ld/intは切り下げであることに注意する
            int i=(int)(new_y_abs_len/mono_length);
            //次に、何列目かを特定する
            ld new_x=center.first+length/2;
            ld new_x_abs_len=abs(new_x);
            //以下、ld/intは切り下げであることに注意する
            int j=(int)(new_x_abs_len/mono_length);
            //以上の操作で、与えられた線分がv[i][j]に存在することがわかった
           
            //v[i][j]=mono_grid_length*grid_weight[i][j];
            return hypot(p1.first-p2.first,p1.second-p2.second)*grid_weight[i][j];
        }
        
        void location(pair<ld,ld>p1,pair<ld,ld>p2){//与えられた線分がグリットを示す二次元vectorのどこに存在するかを調べたあと、代入する
            ld mono_grid_length=hypot(p1.first-p2.first,p1.second-p2.second);
            pair<ld,ld>center=make_pair((p1.first+p2.first)/2,(p1.second+p2.second)/2);
            //まず、何行目かを特定する
            //左上の頂点(-l/2,l/2)を(0,0)と考える   
            ld new_y=center.second-length/2;
            ld new_y_abs_len=abs(new_y);
            //以下、ld/intは切り下げであることに注意する
            int i=(int)(new_y_abs_len/mono_length);
            //次に、何列目かを特定する
            ld new_x=center.first+length/2;
            ld new_x_abs_len=abs(new_x);
            //以下、ld/intは切り下げであることに注意する
            int j=(int)(new_x_abs_len/mono_length);
            //以上の操作で、与えられた線分がv[i][j]に存在することがわかった
           
            v[i][j]=mono_grid_length*grid_weight[i][j];
            
        }
};
class Siddon:public x_ray_vector,public grid{//多重継承
public:
    Siddon(pair<ld,ld>para,pair<ld,ld>cons,int split_number,ld node_length,vector<vector<ld>>weight):x_ray_vector(para,cons),grid(split_number,node_length,weight){}//コンストラクタも継承
    void fragment_grid_x_ray_length(){
        vector<pair<ld,ld>>points;
        for(auto e:x_axis_s){
            auto p=x_axis_to_point(e);
            if(-10<=p.second&&p.second<=10){
                points.push_back(p);    
            }
        }
        for(auto e:y_axis_s){
            auto p=y_axis_to_point(e);
            if(-10<=p.first&&p.first<=10){
                points.push_back(p);    
            }
        }
        struct sort_pred {
            bool operator()(const std::pair<ld,ld> &left, const std::pair<ld,ld> &right) {
                return left.first < right.first;
            }
        };
        sort(points.begin(),points.end(),sort_pred());
           for(int i=0;i<(int)points.size()-1;i++){
            if(points.size()!=0){
                location(points[i],points[i+1]);
            }
        }
        
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<v[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    ld grid_x_ray_legth(){
        vector<pair<ld,ld>>points;
        for(auto e:x_axis_s){
            auto p=x_axis_to_point(e);
            if(-10<=p.second&&p.second<=10){
                points.push_back(p);    
            }
        }
        for(auto e:y_axis_s){
            auto p=y_axis_to_point(e);
            if(-10<=p.first&&p.first<=10){
                points.push_back(p);    
            }
        }
        struct sort_pred {
            bool operator()(const std::pair<ld,ld> &left, const std::pair<ld,ld> &right) {
                return left.first < right.first;
            }
        };
        ld res=0;
        sort(points.begin(),points.end(),sort_pred());
           for(int i=0;i<(int)points.size()-1;i++){
            if(points.size()!=0){
                res+=fragment_length(points[i],points[i+1]);
            }
        }
    }
};

ld theta_converter(ld x,ld y){//x切片,y切片からthetaを孤度法で導出する
    ld tan_theta=y/x;
    return atan(tan_theta);
}
pair<ld,ld> x_ray_rotate(x_ray_vector central_x_ray ,ld theta){//ベクトルを半時計回りにthetaだけ回転させる x_ray_vectorのpara部分のみ考えている
    ld x=central_x_ray.para.first;
    ld y=central_x_ray.para.second;
    ld rotatex=x*cos(theta)-y*sin(theta);
    ld rotatey=y*sin(theta)-y*cos(theta);
    return make_pair(rotatex,rotatey);
}
vector<Siddon>x_rays_generater(Siddon central_x_ray){//グリッドの中心を通るx線一本から左右に広がるx線を生成し、それらをまとめてvectorにして返す
    vector<Siddon>x_rays;
    for(int i=150;i>=1;i--){
        ld theta=theta_converter((i*0.1)/100,100);
        Siddon add_x_ray(x_ray_rotate(central_x_ray,-1*theta),central_x_ray.cons,100,10,central_x_ray.grid_weight);
        x_rays.push_back(add_x_ray);
    }
    for(int i=1;i<=150;i++){
        ld theta=theta_converter((i*0.1)/100,100);
        Siddon add_x_ray(x_ray_rotate(central_x_ray,-1*theta),central_x_ray.cons,100,10,central_x_ray.grid_weight);
        x_rays.push_back(add_x_ray);
    }
}


bool GetContents(const string& filename, vector<vector<string>>& table, const char delimiter = ',')
{
	// ファイルを開く
	fstream filestream(filename);
	if (!filestream.is_open())
	{
		// ファイルが開けなかった場合は終了する
		return false;
	}
 
	// ファイルを読み込む
	while (!filestream.eof())
	{
		// １行読み込む
		string buffer;
		filestream >> buffer;
 
		// ファイルから読み込んだ１行の文字列を区切り文字で分けてリストに追加する
		vector<string> record;              // １行分の文字列のリスト
		istringstream streambuffer(buffer); // 文字列ストリーム
		string token;                       // １セル分の文字列
		while (getline(streambuffer, token, delimiter))
		{
			// １セル分の文字列をリストに追加する
			record.push_back(token);
		}
 
		// １行分の文字列を出力引数のリストに追加する
		table.push_back(record);
	}
 
	return true;
}

int main(){

    // 変数を定義する
	bool status = false;    // メソッドのステータス
	string filename = "stock.csv"; // ファイル名
	vector<vector<string>> table;   // 読み込んだCSVファイルの内容
 
	// CSVファイルの内容を取得する
	status = GetContents(filename, table);
	if (!status)
	{
		// 取得に失敗した場合はエラー終了する
		return -1;
	}
    vector<vector<long double>> weight(100, vector<long double>(100));
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            weight[i][j]=stod(table[i][j]);
        }
    }
    


    const ld eps=0.0000000001;
    vector<vector<Siddon>>all_vectors(360);//all_vectors[角度][何本目]
    //vector<vector<ld>> weight;
    Siddon central_x_ray(make_pair(0,0),make_pair(1,eps),100,10,weight);//cons,paraの順
    for(int i=0;i<360;i++){
        central_x_ray.para=x_ray_rotate(central_x_ray,i);
        all_vectors.push_back(x_rays_generater(central_x_ray));
    }
    
    vector<vector<ld>> result(360,vector<ld>(300));
    for(int i=0;i<360;i++){
        for(int j=0;j<300;j++){
            //Siddon(pair<ld,ld>para,pair<ld,ld>cons,int split_number,ld node_length,vector<vector<ld>>weight)
            result[i][j]=all_vectors[i][j].grid_x_ray_legth();
        }
    }



    //出力したいファイル名を指定する
    std::ofstream outputfile("test.csv");

    //std::vector<std::pair<int,int>>data;
    //出力したいデータを作る
    //data.push_back(std::make_pair(1,3));
    //data.push_back(std::make_pair(4, 3));
    //data.push_back(std::make_pair(1, 2));
    //データの出力
    /*
    for (auto &&b : data) {
        outputfile << b.first;
        outputfile << ',';
        outputfile << b.second;
        outputfile << '\n';
    }
    */
    for(int i=0;i<360;i++){
        for(int j=0;j<300;j++){
            outputfile<<result[i][j];
            outputfile<<',';
        }
        outputfile << '\n';
    }
    //ファイルの出力
    outputfile.close();
    
}

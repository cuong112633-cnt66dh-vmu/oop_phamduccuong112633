#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Xe{
    private:
        int maXe;
        string loaiXe;
        int gioVao;
        int thoiGianDo;
        double phiDoXe;
        bool dangChiemCho;
    public:
        Xe(){
            maXe = 0;
            loaiXe = "";
            gioVao= 0;
            thoiGianDo = 0;
            phiDoXe = 0.0;
            dangChiemCho = false;
        };
        Xe(int ma,const string& loai,int gio,int ThoiLuong){
            maXe=ma;
            loaiXe=loai;
            gioVao=gio;
            thoiGianDo=ThoiLuong;
            phiDoXe = 0.0;
            dangChiemCho=true;
        };
        int layMaXe() const{ return maXe; };
        string layLoaiXe() const{ return loaiXe; };
        int layGioVao() const{ return gioVao; };
        int layThoiGianDo() const{ return thoiGianDo; };
        double layPhiDoXe() const{ return phiDoXe; };
        bool layDangChiemCho() const{ return dangChiemCho; };
        
        void ganMaXe(int ma){ maXe=ma; };
        void ganLoaiXe(const string& loai){ loaiXe=loai; };
        void ganGioVao(int gio){ gioVao=gio; };
        void ganThoiLuongDo(int thoiLuong){ thoiGianDo=thoiLuong; };
        void ganPhiDoXe(double phi){ phiDoXe=phi; };
        void ganDangChiemCho(bool trangThai){ dangChiemCho=trangThai; };
        
        static string chuanHoaLoaiXe(const string& loai){
            if(loai.empty()) return "";
            string kq = loai;
            kq[0] = toupper(kq[0]);
            for (size_t i =1; i < kq.length(); i++){
                kq[i] =tolower(kq[i]);
            }
            return kq;
        };
        
        static bool laLoaiXeHopLe(const string& loai){
            string chuan = chuanHoaLoaiXe(loai);
            return (chuan == "Car" || chuan == "Motorcycle" || chuan == "Bicycle");
        };
        
        void tinhPhiDoXe(){
            double gia = 0.0;
            string loai = chuanHoaLoaiXe(loaiXe);
            if (loai == "Car") gia = 6.00;
            else if (loai == "Motorcycle") gia = 4.00;
            else if (loai == "Bicycle") gia = 2.00;
            double tongPhi = 0.0;
            
            for(int i = 0; i < thoiGianDo; i++){
                int gioHienTai = (gioVao + i) % 24;
                bool laGioCaoDiem = (gioHienTai >= 6 and gioHienTai <=9) || (gioHienTai >= 15 and gioHienTai <=18);
                if(i<2){
                    if(laGioCaoDiem){ tongPhi += gia * 1.30; }
                    else{ tongPhi += gia * 0.95; }
                }
                else{ tongPhi += gia * 0.90; }
            }
            phiDoXe=tongPhi;
        }
        
        void hienThi() const{
            if (dangChiemCho){
                cout << "Ma Xe: " << maXe << " | Loai Xe: " << loaiXe
                     << " | Gio Vao: " << gioVao << " | Thoi Luong: " << thoiGianDo
                     << " | Phi Do Xe: " << phiDoXe << endl;
            }
        };
};

class BaiDoXe{
    private:
        int maBaiDoXe;
        char kichThuoc;
        Xe xe1;
        Xe xe2;
        Xe xe3;
        bool coXe1;
        bool coXe2;
        bool coXe3;
    public:
        BaiDoXe(){
            maBaiDoXe = 0;
            kichThuoc = 'S';
            coXe1 = false;
            coXe2 = false;
            coXe3 = false;
        }
        BaiDoXe(int ma, char kt){
            maBaiDoXe = ma;
            kichThuoc = kt;
            coXe1 = false;
            coXe2 = false;
            coXe3 = false;
        }
        
        int demSoXeHienTai() const {
            int dem = 0;
            if (coXe1) dem++;
            if (coXe2) dem++;
            if (coXe3) dem++;
            return dem;
        }
        
        int layMaBaiDoXe() const { return maBaiDoXe; }
        
        void hienThiXeTheoLoai(const string& loaiCanTim) const {
            if (coXe1 && xe1.layLoaiXe() == loaiCanTim) xe1.hienThi();
            if (coXe2 && xe2.layLoaiXe() == loaiCanTim) xe2.hienThi();
            if (coXe3 && xe3.layLoaiXe() == loaiCanTim) xe3.hienThi();
        }
        
        bool themXe(const Xe& x){
            if (!coXe1){
                xe1 = x;
                coXe1=true;
                return true;
            }
            if ((kichThuoc == 'M' || kichThuoc == 'L') && !coXe2){
                xe2 = x;
                coXe2=true;
                return true;
            }
            if (kichThuoc == 'L' && !coXe3){
                xe3 = x;
                coXe3=true;
                return true;
            }
            return false;
        }
        
        bool xoaXe(int xMa){
            if(coXe1 && xe1.layMaXe() == xMa){
                coXe1 = false;
                return true;
            }
            if(coXe2 && xe2.layMaXe() == xMa){
                coXe2 = false;
                return true;
            }
            if(coXe3 && xe3.layMaXe() == xMa){
                coXe3 = false;
                return true;
            }
            return false;
        }
        
        void tinhTongPhiVaSoLuong(double& tongPhiOto, int& soOto, double& tongPhiXeMay, int& soXeMay, double& tongPhiXeDap, int& soXeDap) const {
            if (coXe1) {
                if (xe1.layLoaiXe() == "Car") { tongPhiOto += xe1.layPhiDoXe(); soOto++; }
                else if (xe1.layLoaiXe() == "Motorcycle") { tongPhiXeMay += xe1.layPhiDoXe(); soXeMay++; }
                else if (xe1.layLoaiXe() == "Bicycle") { tongPhiXeDap += xe1.layPhiDoXe(); soXeDap++; }
            }
            if (coXe2) {
                if (xe2.layLoaiXe() == "Car") { tongPhiOto += xe2.layPhiDoXe(); soOto++; }
                else if (xe2.layLoaiXe() == "Motorcycle") { tongPhiXeMay += xe2.layPhiDoXe(); soXeMay++; }
                else if (xe2.layLoaiXe() == "Bicycle") { tongPhiXeDap += xe2.layPhiDoXe(); soXeDap++; }
            }
            if (coXe3) {
                if (xe3.layLoaiXe() == "Car") { tongPhiOto += xe3.layPhiDoXe(); soOto++; }
                else if (xe3.layLoaiXe() == "Motorcycle") { tongPhiXeMay += xe3.layPhiDoXe(); soXeMay++; }
                else if (xe3.layLoaiXe() == "Bicycle") { tongPhiXeDap += xe3.layPhiDoXe(); soXeDap++; }
            }
        }
        
        void hienThiThongTinBaiDoXe() const {
            cout << "--- Thong tin bai do ---" << endl;
            cout << "Ma Bai Do Xe: " <<  maBaiDoXe << " | Kich Thuoc: " << kichThuoc << endl;
            cout << "Danh Sach Xe Dang Do: " << endl;
            if(coXe1) xe1.hienThi();
            if(coXe2) xe2.hienThi();
            if(coXe3) xe3.hienThi();
            if(!coXe1 && !coXe2 && !coXe3){ cout << "(Bai Do Dang Trong)" << endl; }
        }
};

class HeThongGiaoDien {
private:
    BaiDoXe bai1, bai2, bai3;
    bool coBai1, coBai2, coBai3;

public:
    HeThongGiaoDien() {
        coBai1 = false;
        coBai2 = false;
        coBai3 = false;
    }

    void chayMenu() {
        int luaChon;
        do {
            cout << "\n========== HE THONG QUAN LY BAI DO XE ==========\n";
            cout << "1. Tao Bai do xe moi\n";
            cout << "2. Them xe vao bai do\n";
            cout << "3. Xoa mot Bai do xe\n";
            cout << "4. Lay xe ra khoi bai do\n";
            cout << "5. Hien thi danh sach tat ca cac Bai do xe\n";
            cout << "6. Hien thi danh sach xe theo bai cu the\n";
            cout << "7. Liet ke xe theo loai phuong tien\n";
            cout << "8. Xem bao cao tom tat phi do xe trung binh\n";
            cout << "9. Thoat chuong trinh\n";
            cout << "================================================\n";
            cout << "Nhap lua chon cua ban (1-9): ";
            cin >> luaChon;

            switch (luaChon) {
                case 1: {
                    int maBai; char kichThuoc;
                    cout << "Nhap ma Bai do xe: "; cin >> maBai;
                    if ((coBai1 && bai1.layMaBaiDoXe() == maBai) || (coBai2 && bai2.layMaBaiDoXe() == maBai) || (coBai3 && bai3.layMaBaiDoXe() == maBai)){       
                        cout << "Loi: Ma bai do da ton tai!\n";
                        break;
                    }
                    cout << "Nhap kich thuoc (S/M/L): ";
                    cin >> kichThuoc;
                    kichThuoc = toupper(kichThuoc);
                    if (!coBai1) { 
                        bai1 = BaiDoXe(maBai, kichThuoc); coBai1 = true;
                        cout << "Da tao bai do 1 thanh cong!\n";
                    }
                    else if (!coBai2){
                        bai2 = BaiDoXe(maBai, kichThuoc); coBai2 = true;
                        cout << "Da tao bai do 2 thanh cong!\n";
                    }
                    else if (!coBai3){
                        bai3 = BaiDoXe(maBai, kichThuoc); coBai3 = true;
                        cout << "Da tao bai do 3 thanh cong!\n";
                    }
                    else { cout << "Loi: He thong da dat toi da 3 bai do!\n"; }
                    break;
                }
                case 2: {
                    int maXe, gioVao, thoiLuong; string loaiXe;
                    cout << "Nhap Ma Xe: "; cin >> maXe;
                    cout << "Nhap Loai Xe (Car/Motorcycle/Bicycle): ";
                    cin >> loaiXe;                  
                    if (!Xe::laLoaiXeHopLe(loaiXe)){
                        cout << "Loi: Loai xe khong hop le!\n";
                        break;
                    }
                    loaiXe = Xe::chuanHoaLoaiXe(loaiXe);
                    cout << "Nhap Gio vao (0-23): ";
                    cin >> gioVao;
                    cout << "Nhap Thoi luong do (gio): ";
                    cin >> thoiLuong;
                    Xe xeMoi(maXe, loaiXe, gioVao, thoiLuong);
                    xeMoi.tinhPhiDoXe();
                    bool daThem = false;
                    if (coBai1 && bai1.themXe(xeMoi)) daThem = true;
                    else if (coBai2 && bai2.themXe(xeMoi)) daThem = true;
                    else if (coBai3 && bai3.themXe(xeMoi)) daThem = true;
                    
                    if (daThem) cout << "Da them xe vao bai do thanh cong!\n";
                    else cout << "Loi: Tat ca cac bai deu day hoac khong co bai phu hop voi kich thuoc!\n";
                    break;
                }
                case 3: {
                    int maBai;
                    cout << "Nhap Ma bai do can xoa: ";
                    cin >> maBai;
                    bool daXoa = false;
                    if (coBai1 && bai1.layMaBaiDoXe() == maBai){
                        coBai1 = false;
                        daXoa = true;
                    }
                    else if (coBai2 && bai2.layMaBaiDoXe() == maBai){
                        coBai2 = false;
                        daXoa = true;
                    }
                    else if (coBai3 && bai3.layMaBaiDoXe() == maBai){
                        coBai3 = false;
                        daXoa = true;
                    }
                    if (daXoa) cout << "Da xoa bai do thanh cong!\n";
                    else cout << "Loi: Khong tim thay bai do voi ma nay!\n";
                    break;
                }
                case 4: {
                    int maXe;
                    cout << "Nhap Ma xe can lay ra: ";
                    cin >> maXe;
                    bool daRut = false;
                    if (coBai1 && bai1.xoaXe(maXe)) daRut = true;
                    if (!daRut && coBai2 && bai2.xoaXe(maXe)) daRut = true;
                    if (!daRut && coBai3 && bai3.xoaXe(maXe)) daRut = true;
                    if (daRut) cout << "Da lay xe ra khoi bai thanh cong!\n";
                    else cout << "Loi: Khong tim thay xe!\n";
                    break;
                }
                case 5: {
                    cout << "\n--- DANH SACH BAI DO TONG QUAN ---\n";
                    if (coBai1) bai1.hienThiThongTinBaiDoXe();
                    if (coBai2) bai2.hienThiThongTinBaiDoXe();
                    if (coBai3) bai3.hienThiThongTinBaiDoXe();
                    if (!coBai1 && !coBai2 && !coBai3) cout << "He thong chua co bai do nao.\n";
                    break;
                }
                case 6: {
                    int maBai;
                    cout << "Nhap Ma bai do can xem: "; cin >> maBai;
                    bool timThay = false;
                    if (coBai1 && bai1.layMaBaiDoXe() == maBai){
                        bai1.hienThiThongTinBaiDoXe();
                        timThay = true; }
                    if (coBai2 && bai2.layMaBaiDoXe() == maBai){
                        bai2.hienThiThongTinBaiDoXe();
                        timThay = true;
                    }
                    if (coBai3 && bai3.layMaBaiDoXe() == maBai){
                        bai3.hienThiThongTinBaiDoXe();
                        timThay = true;
                    }                   
                    if (!timThay) cout << "Loi: Khong tim thay bai do!\n";
                    break;
                }
                case 7: {
                    string loaiXe;
                    cout << "Nhap loai xe can tim (Car/Motorcycle/Bicycle): "; cin >> loaiXe;
                    loaiXe = Xe::chuanHoaLoaiXe(loaiXe);
                    
                    cout << "\n--- DANH SACH XE LOAI " << loaiXe << " ---\n";
                    if (coBai1) bai1.hienThiXeTheoLoai(loaiXe);
                    if (coBai2) bai2.hienThiXeTheoLoai(loaiXe);
                    if (coBai3) bai3.hienThiXeTheoLoai(loaiXe);
                    break;
                }
                case 8: {
                    double phiOto = 0, phiXeMay = 0, phiXeDap = 0;
                    int soOto = 0, soXeMay = 0, soXeDap = 0;

                    if (coBai1) bai1.tinhTongPhiVaSoLuong(phiOto, soOto, phiXeMay, soXeMay, phiXeDap, soXeDap);
                    if (coBai2) bai2.tinhTongPhiVaSoLuong(phiOto, soOto, phiXeMay, soXeMay, phiXeDap, soXeDap);
                    if (coBai3) bai3.tinhTongPhiVaSoLuong(phiOto, soOto, phiXeMay, soXeMay, phiXeDap, soXeDap);

                    cout << "\n--- BAO CAO PHI DO XE TRUNG BINH ---\n";
                    cout << fixed << setprecision(2);
                    cout << "- Car        : " << (soOto > 0 ? (phiOto / soOto) : 0.0) << " $\n";
                    cout << "- Motorcycle : " << (soXeMay > 0 ? (phiXeMay / soXeMay) : 0.0) << " $\n";
                    cout << "- Bicycle    : " << (soXeDap > 0 ? (phiXeDap / soXeDap) : 0.0) << " $\n";
                    break;
                }
                case 9:
                    cout << "Da thoat chuong trinh.\n";
                    break;
                default:
                    cout << "Loi: Lua chon khong hop le. Vui long nhap lai!\n";
            }
        } while (luaChon != 9);
    }
};

int main() {
    HeThongGiaoDien heThong;
    heThong.chayMenu();
    return 0;
}
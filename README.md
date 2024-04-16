```
 _______  _______  _______  __   __  _______  __    _             _______  ______   ___      _______ 
|       ||   _   ||       ||  |_|  ||   _   ||  |  | |           |       ||      | |   |    |       |
|    _  ||  |_|  ||       ||       ||  |_|  ||   |_| |   ____    |  _____||  _    ||   |    |____   |
|   |_| ||       ||       ||       ||       ||       |  |____|   | |_____ | | |   ||   |     ____|  |
|    ___||       ||      _||       ||       ||  _    |           |_____  || |_|   ||   |___ | ______|
|   |    |   _   ||     |_ | ||_|| ||   _   || | |   |            _____| ||       ||       || |_____ 
|___|    |__| |__||_______||_|   |_||__| |__||_|  |__|           |_______||______| |_______||_______|
```
# 1. Giới thiệu Game
Trong một thế giới đầy mê cung và nguy hiểm, Pacman đối mặt với thị trấn bị UFO xâm chiếm. Sử dụng sức mạnh từ trái chuối vàng, anh dấn thân vào cuộc hành trình khám phá và giải cứu. Trải qua mê cung, anh phải đối mặt với những cặm bẫy và thách thức từ những kẻ ngoại đạo tàn ác không có tay. Bằng sự can đảm và khéo léo tận dụng những vật phẩm trong mê cung, anh chinh phục mọi thử thách, vượt qua mọi rủi ro để đánh bại người ngoài hành tinh và tái lập hòa bình cho thị trấn. Cuối cùng, Pacman trở thành biểu tượng của sự hy vọng và chiến thắng.

# 2. Main menu
- Ngay ở màn hình chờ, ta đã thấy được Impostor và Pacman rượt nhau xuyên màn hình.
- Ta có thể bẳt đầu game bằng cách nhấn nút PLAY.
- Điều chỉnh âm lượng bằng thanh âm lượng dưới chữ VOLUME.
- Bạn có thể thoát ra bằng nút QUIT.
- Ta có thể chiêm ngưỡng dung nhan của 2 tác giả ở 2 góc màn hình.
![](assets/MainMenuPreview.png)
- Không chỉ thế, ta còn có thể nhấn MAPS để lựa chọn 1 trong 4 map khác nhau:
  - Map gốc
  - Map cải tiến
  - Map yêu trường
  - Map luyện tập
![](assets/MapPreview.png)
# 3. Chơi Game
- Sau khi chọn map và nhấn PLAY, bạn sẽ có thể bắt đầu tận hưởng tựa game này.
- Game sẽ cho bạn chuẩn bị trong vòng 3s.
![](assets/InGame.png)
- Để giành được chiến thắng trước những tên ngoài hành tinh gian ác và sặc sỡ này, ta cần di chuyển khôn khéo để tránh những thế lực hắc ám và ăn hết ***tất cả*** các đốm trắng trên màn hình.
- Như có thể thấy, chúng ta có những vật phẩm đồng hành trên con đường giành lại chính nghĩa. Tuy nhiên, sau mỗi trận rượt đuổi gay go, những vật phẩm sẽ được sinh ra *hoàn toàn ngẫu nhiên* theo một thuật toán phức tạp!
- Các vật phẩm:
  - <span style = "color : purple">Trái ác quỷ</span> (Gomu Gomu no Mi) ban tặng cho Pacman sức hủy diệt kinh hoàng trong một khoảng thời gian có hạn: ![](assets/Powerup.png)
  - <span style = "color : cyan">Tia sét</span> của thần Zeus đem lại cho Pacman tốc độ ánh sáng c = 299 792 458 m/s để anh bỏ xa các tên ngoài hành tinh háu ăn: ![](assets/Lightning.png)
  - <span style = "color : red">Trái tim</span> của Aphrodite ban cho Pacman thêm một cơ hội làm lại cuộc đời (nếu Pacman đã mất mạng): ![](assets/heart.png)
  - <span style = "color : orange">Cánh cửa</span> <span style = "color : blue">thần kì</span> (どこでもドア) của Doraemon giúp Nobi-pac được phen thoát chết khi bị dí ép góc: ![](assets/Portal2.png)  ![](assets/Portal1.png) (chắc chắn không phải từ game Portal)
- Nếu bạn muốn nhân vật Pacman của mình trụ thêm được ít lâu thì bạn có thể bấm SPACE để pause game, màn hình sẽ hiện ra một màn hình tạm dừng. Ở đó, bạn có thể thấy hình ảnh một tên ngoài hành tinh nham hiểm và một chú Pacman cute phomaique. Bạn có thể bấm quit to menu để tránh phải xem cảnh giết người kinh dị của những tên khát máu với chú Pacman yếu đuối hoặc có thể tiếp tục để chứng kiến cảnh Pacman bị dí đến chết.
![](assets/PauseGamePreview.png)
- Nếu như may mắn giành được chiến thắng, bạn sẽ được nhận một phần thưởng bất ngờ 🎆 🎇.

# 4. Khác
## Hoạt ảnh
Hoạt ảnh của Impostor được tác giả tự sáng tác dưới 3 dạng khác nhau:

![](assets/Sus.gif) *- Impostor trong chế độ săn lùng người chơi*

![](assets/SusNervous.gif) *- Impostor cảm thấy không ổn lắm sau khi người chơi cắn trái ác quỷ ![](assets/Powerup.png)*

![](assets/SusDead.gif) *- Impostor bị người chơi gặm mất nửa người và bỏ chạy về nhà mách mẹ*
## AImpostor
![Sus.gif](assets%2FSus.gif) *- Chiến thuật đơn giản và có vẻ hiệu quả: ***Nhắm thẳng*** tới bạn*

![SusPink.gif](assets%2FSusPink.gif) *- Dự đoán trước hướng đi bạn sắp tới và ***đón đầu*** bạn*

![SusGreen.gif](assets%2FSusGreen.gif) *- Thường xuyên ***phối hợp*** với <span style="color:red">Impostor đỏ</span> để chặn đầu bạn*

![SusBrown.gif](assets%2FSusBrown.gif) *- Cơ chế vô cùng đặc biệt và ***khó đoán****

## Credits

- Dưới công sức của [mình](https://github.com/lephantriduc) và [bạn mình](https://github.com/hieupy2k5).
- [Tác giả của một trong hai tựa game gốc chúng mình lấy ý tưởng](https://en.wikipedia.org/wiki/Toru_Iwatani)
- [Công ty của tựa game còn lại](https://www.innersloth.com)


```
. 　　　。　　　　•　 　ﾟ　　。 　　.

　　　.　　　 　　.　　　　　。　　 。　. 　

.　　 。　　　　　 ඞ 。 . 　　 • 　　　　•

　　ﾟ　　 SusRed was An Impostor.　 。　.

　　'　　　 3 Impostors remain 　 　　。

　　ﾟ　　　.　　　. ,　　　　.　 .
```

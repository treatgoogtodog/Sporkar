# Sporkars

## Nguyễn Ngọc Bảo - 24022768

**Sporkar** là một tựa game lấy bối cảnh hậu tận thế, trong đó nhân vật chính là một người di cư lánh nạn từ vùng Nam Mĩ xuống Mexico. Người điều khiển cần phải điều khiển nhân vật vượt qua vật cản, đi xa nhất có thể, nhân vật chính có khả năng tránh né mọi vật cản trong thời gian ngắn.

# Ngưỡng điểm nhắm tới 8.5 - 9.5
- Thuật toán kiểm tra va chạm [AABB](https://en.wikipedia.org/wiki/Bounding_volume#:~:text=In%20many%20applications,to%20be%20recomputed.) kiểm tra va chạm theo hệ trục toạ độ.
-Thuật toán

- Game có đồ hoạ tương đối đơn giản, sử dụng animation cho nhân vật, các vật cản và GUI là tự vẽ bằng [Asesprite](https://www.aseprite.org/). Các thành phần GUI và Texture nhân vật được vẽ và mapping sử sụng [Free Texture Packer](https://free-tex-packer.com/app/) để giảm thiểu số lượng texture cần sử dụng.
- Cơ chế mang sự tương đồng với [Dino](https://chromedino.com/), được cải tiến nhiều mặt về hình ảnh âm thanh và cơ chế.
### Các tính năng được thêm vào:
- Paralax background: Nền được xây dựng bởi nhiều lớp và có chênh lệch về độ dời tạo nên chiều sâu của cảnh vật với 5 lớp chứa speed khác nhau.
- Thanh máu / Thanh kỹ năng: Được render bằng tỷ lệ phần trăm thanh máu * chiều rộng của thanh. Thanh kỹ năng được thiết kế để chỉ hồi lại khi đã dùng hết.
- Âm thanh khi nhảy, bị thương, di chuột vào nút bấm và bấm nút:Khi nhảy có thể phát ra 2 kiểu âm thanh và 4 khi bị thương.
- Các nút bấm có sự tương tác với con trỏ chuột, nhô lên và hạ xuống theo chuyển động giả hồi quy bằng hàm bậc hai
- Các thành phần UI như `PauseMenu`, `Gameover` Mang dạng pop-up trượt vào, tạo ra chuyển cảnh mượt mà giữa các trạng thái theo chuyển động hồi quy
- Âm lượng nhạc và âm thanh có thể thay đổi tuỳ ý nhờ có slider mà không chỉ cố định vào bật // tắt.
- Hiển thị điểm số và quãng đường đi trực tiếp trên GUI màn chơi
- Bảng điểm cao tổng hợp 5 điểm cao nhất từ file .sav
- Âm nhạc thêm tự chọn với mọi file .mp3 trong `./Music`
- Cài đặt phối hợp các lớp quản lý `SDL_Manager` `SoundManager` `Texthandler` `GUIHander` tiện lợi cho việc thêm tính năng và cài đặt các hàm/màn chơi mới.
-Các tài nguyên header/asset được sắp xếp hợp lý, dễ truy cập

```
├───Debug
├───Fonts Các [font](https://fonts.google.com/)
├───Headers <- thư viện
├───Music <- Nhạc tự chọn (import file mp3 vào đây)
├───MyGame
│   ├───Debug
│   │   └───MyGame.tlog
│   └───x64
│       └───Debug
│           └───MyGame.tlog
├───Save
├───SFX <- Các SFX
├───Sprite
│   ├───aerialobs
│   ├───Bg
│   ├───Biker
│   │   ├───Biker-Crouch
│   │   ├───Biker-IDLE
│   │   ├───Biker-Jump
│   │   ├───Biker-Run
│   │   └───Biker-Walk
│   ├───GUI <- Thành phần GUI
│   ├───PlayerSpr
│   └───roadobs
├───Texture
├───TMusic
├───Voiceline 
└───x64
    ├───Build
    └───Debug
```

# Source:

- Chuyển động nội suy [Lerp](https://youtu.be/YJB1QnEmlTs?si=m_fdWF3WmcAygwfm), chuyển động giả nội suy.
- Cài đặt thư viện, quản lý tài nguyên SDL [lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php)
- Đọc json spritesheet [nlohmann/json](https://github.com/nlohmann/json) 

# Demo
[Youtube](https://youtu.be/ahzGHlwbtVg)
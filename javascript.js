const menuBar = document.querySelector('#menu-bar');
const navbar = document.querySelector('.navbar');

// Sử dụng biến toàn cục cho slideshow
let slideIndex = 0;

// Khi tài liệu đã sẵn sàng
document.addEventListener('DOMContentLoaded', function() {
  // Thiết lập menu toggle
  setupMenuToggle();
  
  // Khởi chạy slideshow nếu có các slide
  const slides = document.getElementsByClassName("mySlides");
  if (slides.length > 0) {
    showSlides();
  }
  
  // Thiết lập chức năng "Thêm vào giỏ hàng"
  setupAddToCart();
});

// Xử lý menu toggle
function setupMenuToggle() {
  menuBar.addEventListener('click', () => {
    menuBar.classList.toggle('fa-times'); // Sửa từ fa-time thành fa-times
    navbar.classList.toggle('active');
  });

  // Đóng menu khi cuộn trang
  window.addEventListener('scroll', () => {
    menuBar.classList.remove('fa-times');
    navbar.classList.remove('active');
  });
}

// Hàm hiển thị slideshow cải tiến
function showSlides() {
  const slides = document.getElementsByClassName("mySlides");
  
  // Ẩn tất cả slides
  for (let i = 0; i < slides.length; i++) {
    slides[i].style.display = "none";
  }
  
  // Tăng index và reset nếu cần
  slideIndex++;
  if (slideIndex > slides.length) {
    slideIndex = 1;
  }
  
  // Hiển thị slide hiện tại
  slides[slideIndex - 1].style.display = "block";
  
  // Lặp lại sau 2 giây
  setTimeout(showSlides, 2000);
}

// Thiết lập chức năng "Thêm vào giỏ hàng"
function setupAddToCart() {
  // Kiểm tra xem jQuery có sẵn không
  if (typeof jQuery !== 'undefined') {
    // Sử dụng jQuery nếu có
    $(".add-to-cart").click(function(e) {
      e.preventDefault(); // Ngăn chặn hành vi mặc định của liên kết
      const name = $(this).data("name");
      const price = parseFloat($(this).data("price"));
      
      // Thêm sản phẩm vào giỏ hàng
      addProductToCart(name, price);
    });
  } else {
    // Sử dụng JavaScript thuần nếu không có jQuery
    document.querySelectorAll(".add-to-cart").forEach(button => {
      button.addEventListener("click", function(e) {
        e.preventDefault();
        const name = this.getAttribute("data-name");
        const price = parseFloat(this.getAttribute("data-price"));
        
        // Thêm sản phẩm vào giỏ hàng
        addProductToCart(name, price);
      });
    });
  }
}

// Hàm thêm sản phẩm vào giỏ hàng
function addProductToCart(name, price) {
  // Bạn có thể thay đổi alert thành một thông báo đẹp hơn
  const formattedPrice = price.toFixed(2);
  
  // Tạo một thông báo nổi tạm thời
  const notification = document.createElement('div');
  notification.className = 'cart-notification';
  notification.innerHTML = `Đã thêm <strong>${name}</strong> vào giỏ hàng. Giá: $${formattedPrice}`;
  
  // Thêm thông báo vào body
  document.body.appendChild(notification);
  
  // Xóa thông báo sau 3 giây
  setTimeout(() => {
    notification.classList.add('fadeOut');
    setTimeout(() => {
      document.body.removeChild(notification);
    }, 500);
  }, 2500);
  
  // Ở đây bạn có thể thêm code để lưu sản phẩm vào localStorage hoặc gửi yêu cầu đến server
  saveToCart(name, price);
}

// Hàm lưu sản phẩm vào localStorage
function saveToCart(name, price) {
  let cart = JSON.parse(localStorage.getItem('cart')) || [];
  
  // Kiểm tra xem sản phẩm đã có trong giỏ hàng chưa
  const existingItem = cart.find(item => item.name === name);
  
  if (existingItem) {
    // Nếu đã có, tăng số lượng
    existingItem.quantity += 1;
  } else {
    // Nếu chưa có, thêm mới
    cart.push({
      name: name,
      price: price,
      quantity: 1
    });
  }
  
  // Lưu giỏ hàng đã cập nhật vào localStorage
  localStorage.setItem('cart', JSON.stringify(cart));
}
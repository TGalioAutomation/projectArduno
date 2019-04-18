angular.module('myApp', [
    'ngRoute',
    'mobile-angular-ui',
	'btford.socket-io'
]).config(function($routeProvider) {
    $routeProvider.when('/', {
        templateUrl: 'home.html',
        controller: 'Home'
    });
}).factory('mySocket', function (socketFactory) {
	var myIoSocket = io.connect('/webapp');	//Tên namespace webapp

	mySocket = socketFactory({
		ioSocket: myIoSocket
	});
	return mySocket;
	
/////////////////////// Những dòng code ở trên phần này là phần cài đặt, các bạn hãy đọc thêm về angularjs để hiểu, cái này không nhảy cóc được nha!
}).controller('Home', function($scope, mySocket) {
	////Khu 1 -- Khu cài đặt tham số 
    //cài đặt một số tham số test chơi
	//dùng để đặt các giá trị mặc định
	$scope.CamBienMua = "Không biết nữa ahihi, chưa thấy có thằng nào cập nhập hết";
	$scope.leds_status = [true,true,true,true,true,true,true,true,true]
	$scope.leds_status2 = [true,true,true,true,true,true,true,true]
	$scope.lcd = ["", ""]
	$scope.servoPosition = 0
	$scope.buttons = [] //chả có gì cả, arduino gửi nhiêu thì nhận nhiêu!
	
	////Khu 2 -- Cài đặt các sự kiện khi tương tác với người dùng
	//các sự kiện ng-click, nhấn nút
	$scope.updateSensor  = function() {
		mySocket.emit("RAIN")
	}
	$scope.updateStatus =  function() {
		for (var index = 0; index < $scope.leds_status.length; index++) {
			if($scope.leds_status[index] == false){
				document.getElementById("status" + index).firstElementChild.className = "status-OFF";
				document.getElementById("button" + index).firstElementChild.className = "Button-OFF";
			}else{
				document.getElementById("status" + index).firstElementChild.className = "status-ON";
				document.getElementById("button" + index).firstElementChild.className = "Button-ON";
			}
		}
	}
	
	//Cách gửi tham số 1: dùng biến toàn cục! $scope.<tên biến> là biến toàn cục
	$scope.changeLED = function() {
		console.log("send LED ", $scope.leds_status)
		var json = {
			"led": $scope.leds_status
		}
		mySocket.emit("LED", json)
	}
	$scope.setstatusDevice9 = function(){
		$scope.leds_status[8] = !$scope.leds_status[8]
		$scope.changeLED()
	}
	$scope.setstatusDevice8 = function(){
		$scope.leds_status[7] = !$scope.leds_status[7]
		$scope.changeLED()
	}
	$scope.setstatusDevice7 = function(){
		$scope.leds_status[6] = !$scope.leds_status[6]
		$scope.changeLED()
	}
	$scope.setstatusDevice6 = function(){
		$scope.leds_status[5] = !$scope.leds_status[5]
		$scope.changeLED()
	}
	$scope.setstatusDevice5 = function(){
		$scope.leds_status[4] = !$scope.leds_status[4]
		$scope.changeLED()
	}
	$scope.setstatusDevice4 = function(){
		$scope.leds_status[3] = !$scope.leds_status[3]
		$scope.changeLED()
	}
	$scope.setstatusDevice3 = function(){
		$scope.leds_status[2] = !$scope.leds_status[2]
		$scope.changeLED()
	}
	$scope.setstatusDevice2 = function(){
		$scope.leds_status[1] = !$scope.leds_status[1]
		$scope.changeLED()
	}
	$scope.setstatusDevice1 = function(){
		$scope.leds_status[0] = !$scope.leds_status[0]
		$scope.changeLED()
	}
	//Khi nhận được lệnh LED_STATUS
	mySocket.on('LED_STATUS', function(Json) {
		console.log("Name: " + Json.LED_STATUS);
		$scope.leds_status = Json.LED_STATUS
		for (var index = 0; index < $scope.leds_status.length; index++) {
			if($scope.leds_status[index] == false){
				document.getElementById("status" + index).firstElementChild.className = "status-OFF";
				document.getElementById("button" + index).firstElementChild.className = "Button-OFF";
			}else{
				document.getElementById("status" + index).firstElementChild.className = "status-ON";
				document.getElementById("button" + index).firstElementChild.className = "Button";
			}
		}
		$scope.updateStatus()
	})
	mySocket.on('connect', function() {
		console.log("connected")
	})
		
});
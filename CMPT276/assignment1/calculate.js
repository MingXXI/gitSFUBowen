/***
 * For the brave souls who get this far: You are the chosen ones,
 * the valiant knights of programming who toil away, without rest,
 * fixing our most awful code. To you, true saviors, kings of men,
 * I say this: never gonna give you up, never gonna let you down,
 * never gonna run around and desert you. Never gonna make you cry,
 * never gonna say goodbye. Never gonna tell a lie and hurt you.
 */
/***
 * 致终于来到这里的勇敢的人：
 * 你是被上帝选中的人，是英勇的、不敌辛苦的、不眠不休的来修改我们这最棘手的代码的编程骑士。
 * 你，我们的救世主，人中之龙，我要对你说：永远不要放弃，永远不要对自己失望，永远不要逃走，辜负了自己，
 * 永远不要哭啼，永远不要说再见，永远不要说谎来伤害自己。
 */


var grades = [65.95, 56.98, 78.62, 96.1, 90.3, 72.24, 92.34, 60.00, 81.43, 86.22, 88.33, 9.03,
 49.93, 52.34, 53.11, 50.10, 88.88, 55.32, 55.69, 61.68, 70.44, 70.54, 90.0, 71.11, 80.01];
 // https://www.w3schools.com/js/js_array_sort.asp

window.onload = function() {
	window.alert('Please Type in Grade as Numbers \nPress Enter to Update Form');
	display();
};

function keyup_submit(e){ 
	var evt = window.event || e; 
		if (evt.keyCode == 13){
			display();
	} 
} //Action of Enter refer to: https://blog.csdn.net/qq_37131111/article/details/78392979

function display(){
	var visualize = document.getElementsByName("visualize");
	var grade_element = document.getElementsByTagName("input");
	var stats = document.getElementsByName("stats");
	var histogram = new Array(11).fill(0);
	var lower_bounds = [];

	for (var i=0; i<12; i++){
		lower_bounds[i] = parseFloat(grade_element[i].value);
		//Function to grab number from string, Refer to: https://www.runoob.com/jsref/jsref-parsefloat.html

		if (isNaN(lower_bounds[i]) || lower_bounds[i] > 100 || lower_bounds[i] < 0 || lower_bounds[i] >= lower_bounds[i-1]){
			for (var j=0; j<histogram.length; j++){
				visualize[j].style.width = 180 + "px";
				visualize[j].innerHTML = 'Invalid Input';
			}
			window.alert('Please Check Your Input');
			return;
		}
	}

	for(i=1; i<12; i++){
		for(var j=0; j<grades.length; j++){
			if(i == 1){
				if(grades[j]>=lower_bounds[i]){
					histogram[i-1]++;
				}
			}else if(grades[j]>=lower_bounds[i] && grades[j]<lower_bounds[i-1]){
				histogram[i-1]++;
			}
		}
	}


	for (i=0; i<histogram.length; i++){
		visualize[i].style.width = 10 * histogram[i] + "px";
		visualize[i].innerHTML = histogram[i];
	}
}


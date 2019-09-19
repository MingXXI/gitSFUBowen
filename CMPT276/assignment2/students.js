function validInsert(){
	var message1 = document.getElementById("message1");
	// var message2 = document.getElementById("message2");
	var data1 = document.getElementById("form1");
	var name = data1[0].value
	// var gender = data1[1].checked?"M":data1[2].checked?"F":"O"
	var weight = parseFloat(data1[4].value)
	var height = parseFloat(data1[5].value)
	var color = data1[6].value
	var gpa = parseFloat(data1[7].value)


	message = ""

	if (name.length==0)
		message += " name "

	if (isNaN(weight)||weight<=0)
		message += " weight "

	if (isNaN(height)||height<=0)
		message += " height "

	if (color.length==0)
		message += " color "

	if (isNaN(gpa)||gpa<0)
		message += " gpa "

	if (message!=""){
		message1.innerHTML = "<b>"+ message + "invalid</b>"
		message1.style.color = "#ff0000"
		return false
	}
		
	else{
		message1.innerHTML = "<b>Please fill out the student's info to insert</b>"
		message1.style.color = "#000000"
		return true
	}
}

function validSearch(){
	var message1 = document.getElementById("message2");
	// var message2 = document.getElementById("message2");
	var data1 = document.getElementById("form2");
	var name = data1[0].value
	// var gender = data1[1].checked?"M":data1[2].checked?"F":"O"
	// var weight = parseFloat(data1[4].value)
	// var height = parseFloat(data1[5].value)
	// var color = data1[6].value
	// var gpa = parseFloat(data1[7].value)


	message = ""

	if (name.length==0)
		message += " name "

	// if (isNaN(weight)||weight<=0)
	// 	message += " weight "

	// if (isNaN(height)||height<=0)
	// 	message += " height "

	// if (color.length==0)
	// 	message += " color "

	// if (isNaN(gpa)||gpa<0)
	// 	message += " gpa "

	if (message!=""){
		message1.innerHTML = "<b>"+ message + "invalid</b>"
		message1.style.color = "#ff0000"
		return false
	}
		
	else{
		message1.innerHTML = "<b>Please enter the student's name to search/edit/delete</b>"
		message1.style.color = "#000000"
		return true
	}
}
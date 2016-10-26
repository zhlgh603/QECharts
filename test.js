<script type="text/javascript">
  var Test={
    createDiv:function(){
      var div = document.createElement('div');
      div.id="createDiv";
      div.style.cssText = 'border:1px solid red; width:200px; z-index:100; height:20px;';
      document.body.appendChild(div);
    },
    appendDivChild:function(){
      var div = document.createElement('div');
      div.id="appendDivChild";
      div.style.cssText = 'border:1px solid green; width:400px; z-index:100; height:100px;';
      var childDiv= document.createElement('div');
      childDiv.id="childDiv";
      childDiv.style.cssText = 'border:2px solid gray; width:200px; z-index:100; height:50px;';
      div.appendChild(childDiv);
      document.body.appendChild(div);
    },
    createSelect:function(){
      var select=document.createElement('select');
      select.id="select";
      var option1=document.createElement('option');
      option1.value=1;
      option1.text=1;//非ie,添加内容
      option1.innerHTML=1;//ie,添加内容
      select.appendChild(option1);
      var option2=document.createElement('option');
      option2.value=2;
      option2.text=2;
      option2.innerHTML=2;
      select.appendChild(option2);
      var option3=document.createElement('option');
      option3.value=3;
      option3.text=1;
      option3.innerHTML=3;
      select.appendChild(option3);
      document.body.appendChild(select);
    },
    createRadio:function(){
      var radio=document.createElement('input');
      radio.id='radio';
      radio.type="radio";
      radio.width="100";
      var label=document.createElement('label');
      label.text="男";
      label.innerHTML="男";
      document.body.appendChild(radio);
      document.body.appendChild(label);
    }
  };
  Test.createDiv();//创建div
  Test.appendDivChild();//为追加子div
  Test.createSelect();//创建下拉框
  Test.createRadio();//创建单选按钮
</script>

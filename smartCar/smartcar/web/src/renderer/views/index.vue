<template>
<div>

	障碍物距离:{{del(list)[1]}}cm, <br>
	小车当前状态:{{state(del(list)[2])}}
</div>
</template>

<script>
var net = require('net');
export default {
	data(){
		return{
			//host:'127.0.0.1',
			//port:'8888',
			host:'172.19.3.30',
			port:'8899',
			list:'',
		}
	},
	created(){
/**/
		const that = this
		var client = new net.Socket();
		client.connect(this.port, this.host, function() {

		    console.log('CONNECTED TO: ' + this.host + ':' + this.port);
		    // 建立连接后立即向服务器发送数据，服务器将收到这些数据
		    client.write('Hello!');
		});
		// 为客户端添加“data”事件处理函数
		// data是服务器发回的数据
		client.on('data', function(data) {

		    //console.log('DATA: ' + data);
		    that.list = data+''//JSON.parse('['++']')
		    // 完全关闭连接
		    //client.destroy();
		});

		// 为客户端添加“close”事件处理函数
		client.on('close', function() {
		    console.log('Connection closed');
		});
	},
	methods:{
		del(tmp){
			let data =  tmp.split("|")
			let rst = data[data.length-2]
			console.log(data)
			return rst.split(",")
		},
		state(s)
		{
			if(s==0) return "停止"
			else if(s==1)return "直行中"
			else if(s==2)return "左转"
			else if(s==3)return "右转"
			else if(s==4)return "后退"
			else return "未知"
		}
	}
}
</script>

<style>
  /* CSS */
</style>

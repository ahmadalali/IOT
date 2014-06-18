(function () {

			var deviceList = $('#peeps'),
				users =[];

            var button = PUBNUB.$('dashboard');
        //    var image = PUBNUB.$('image');
            var pubnub = PUBNUB.init({
                publish_key: 'demo',
                subscribe_key: 'demo',
                UUID: '***********TEST************'
            });

            // sending a reply to the server
            pubnub.bind('click', button, function () {
                pubnub.publish({
                    channel: 'button-reply',
                    presence: function(m){console.log(m)},
                    message: $('#clientText').val()
                   
                });
            });

            pubnub.subscribe({
                channel: 'button-reply',
                 message: function(m){console.log(m)},
                 presence: function(message,env,channel){
                	
                	if(message.action == "join"){
                		users.push(message.uuid);
                		deviceList.append("<li style =text-align:center>" + message.uuid + "</li>");
                	}
                	else{
          				users.splice(users.indexOf(message.uuid), 1);
          				deviceList.find('[data-username="' + message.uuid + '"]').remove();
        			}

      
      
                		
                }
            });

            // receiving the messages from the server
            pubnub.subscribe({
                channel: 'button-click',
                presence: function(m){console.log(m)},
               message: function(m){console.log(m)}
               //server_button_click
                
            });
            
 		    	
 			
            
            // action when message received from the server
      /*    function server_button_click(message) {
                $('#chat').append("<div class='bubbledLeft'>" + message + "</div>");
            }*/
        
        pubnub.here_now({
     			channel : 'button-reply',
     			callback : function(m){console.log(m)},
     			state:true
 			});
        	   
        
        })();
<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of authmodel
 *
 * @author Alex
 */
class authmodel {
    
    
    final public function cheak($post=NULL){
	
		if($post!=NULL){
			if(empty($post['user_login']) || empty($post['user_password'])  )
				$response['error_message'] = 'Не все данные ввведены... ';
			else{
                           
				$user_login = db::quote(trim($post['user_login']));
				$user_password = trim($post['user_password']);
				$query =  db::GetRow("SELECT id,user_password,user_tpl_id FROM users WHERE user_login = $user_login");
				
                                if($query != 0){					
					if($query['user_password'] === md5($user_password)){
						$response['user_admin_id'] = $query['id'];                                                
						
                                                $userTpl = db::GetAll("SELECT uva_id,key_val FROM users_templates 
                                                                       WHERE utpl_id=".$query['user_tpl_id']);
                                                
                                                foreach ($userTpl as $key => $value):                                                    
                                                        $userArray['ua'.$value['uva_id']] = $value['key_val'];                                                                                                   
                                                endforeach; 
                                                $response['user_tpl'] = $userArray;
                                                
					}else{
						$response['error_message'] = 'Не верно введен логин или пароль...';
					}
				}else{                                    
					$response['error_message'] = 'Не верно введен логин или пароль...';
				}
			}					
		}
	return @$response;	
    }
    final public function user_info($user_id){
        $data =  db::GetRow("SELECT id,user_login,user_name FROM users WHERE id=".$user_id);
        
        return $data;
    }
    final public function usersList(){
        
        switch($_SESSION['user_type']):
            case '1':
                $data= db::GetAll("SELECT id,user_name FROM users ");
                break;
            default:
                $data= db::GetAll("SELECT id,user_name FROM users WHERE user_tpl_id!=1");
                break;
        endswitch;        
        return $data;
    }
    public function createUser($post){
        if(empty($post['user_login'])||
           empty($post['user_name'])||
           empty($post['user_password'])||
           empty($post['user_password_confirm'])):
            
            $data['error'] = FALSE;
            $data['message'] = "Не все данные введены для создания пользователя";
            return $data;
        endif;
        
        if($post['user_password'] != $post['user_password_confirm']):
            $data['error'] = FALSE;
            $data['message'] = "Ведденые пароли не совпадают";
            return $data;
        endif;    
        
        $user_login = db::quote(trim($post['user_login']));
	
	$query =  db::GetRow("SELECT id FROM users WHERE user_login = $user_login");
	
        if($query!=0):
            $data['error'] = FALSE;
            $data['message'] = "Пользователь с данным логином уже зарегестрирован";
            return $data;    
        endif;
        
        $user_password = md5(trim($post['user_password']));
        $user_name = db::quote(trim($post['user_name']));
        
        db::execute("INSERT INTO users (user_login,user_name,user_password,user_tpl_id,user_status_id) 
                     VALUES ($user_login,$user_name,'$user_password',".$post['user_tpl_id'].",1)");
        $data['error'] = TRUE;
        return $data;
    }
    final public function updateUser($post,$userId){        
        
        $user_login = db::quote(trim($post['user_login']));
        $user_name = db::quote(trim($post['user_name'])); 
        
        if(!empty($post['user_password'])):
            $user_password = db::quote(md5(trim($post['user_password'])));
            db::execute("UPDATE users SET user_login=$user_login,user_name=$user_name,user_password=$user_password 
                         WHERE id=".$userId);
        else:
            db::execute("UPDATE users SET user_login=$user_login,user_name=$user_name  WHERE id=".$userId);
        endif;     
    }
}

?>

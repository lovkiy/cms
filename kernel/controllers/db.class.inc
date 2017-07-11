<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Класс который отвечает за обработку всех запроссов 
 * к базе данных я буду использовать универсальный метод
 * работы с базами данных испльзуя PDO
 * 
 * @author Alex
 */
class db {
  
  /*
   * Будет содержать линк соиденения с базой данных
   */
  private static $_conn;

  /*
   * Нужно чтобы конструктор был приватным для 
   * предостержения непосредственного запуска класса
   */
  private function __construct(){}
  
  /*
   * Метод в зависимости от драйвера устанавливает 
   * правильный DSN
   * TODO: Я написал только подключение к базе данных mysql
   * Нужно еще дописать подключение как минимум к 
   * mssql, sqli, postregeSQL
   */
  
  private static function _dbDriver(){
     
    switch (config::$config['db']['dbdriver']) {
        case 'mysql':           
            $dsn = config::$config['db']['dbdriver'] . 
                   ":host=".config::$config['db']['hostname']. 
                   ";dbname=".config::$config['db']['database'];
            
            $atr = array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES '".config::$config['db']['char_set']."'");
            
            $dataconn = array('pdo_dsn'=>$dsn,
                             'db_username'=>config::$config['db']['username'],
                             'db_password'=>config::$config['db']['password'],
                             'db_atribute'=>$atr);
            break;
    }
    return $dataconn; 
  }
  /*
   *Метод устанавлюющий соиденение с базой данных 
   * 
   */
  
  private static function connect(){   
      
     extract(self::_dbDriver(), EXTR_OVERWRITE);

    // Создает соиденение с базой данных только в том случае если его небыло
    if (!isset(self::$_conn)){
      // Ловим потенциальные ошибки исключений
      try{      
          
        self::$_conn = new PDO($pdo_dsn, $db_username, $db_password, $db_atribute);       
        self::$_conn->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
        
      }catch (PDOException $e){
        
        self::Close();
        trigger_error($e->getMessage(), E_USER_ERROR);
      }
    }
    //Возвращаем линк соидинения
    return self::$_conn;
  }
  
  /*
   *Очищает соиденение 
   */
  
  public static function Close(){
    self::$_conn = null;
  }
  
  /*
   * Мктод обертка для  PDOStatement::execute()
   * выполняет запрос к базе данных
   * подготавливает запрос и добавляет в него параметры
   * они нужны для передачи их в процедуру
   */
  
  public static function execute($sqlQuery, $params = null){
    
    try{
     
      $database_handler = self::connect();
     
      $statement_handler = $database_handler->prepare($sqlQuery);     
      $statement_handler->execute($params);
      
    }catch(PDOException $e){
     
      self::Close();
      trigger_error($e->getMessage(), E_USER_ERROR);
    }
  }
  
  /*
   * Метод обертка для PDOStatement::fetchAll()
   * получаем все элементы из базы данных 
   * по запроссу в ассоциативном массиве
   */
  
  public static function GetAll($sqlQuery, $params = null,
                                $fetchStyle = PDO::FETCH_ASSOC)
  {
    // Задаем по умолчанию возвращаемое значение в NULL
    $result = null;

    
    try{
     
      $database_handler = self::connect();
    
      $statement_handler = $database_handler->prepare($sqlQuery);     
      $statement_handler->execute($params);  
      
      // Получаем ассоциативный массив по заданному запросу
      $result = $statement_handler->fetchAll($fetchStyle);
     
    }catch(PDOException $e){
     
      self::Close();
      trigger_error($e->getMessage(), E_USER_ERROR);
    }
    return $result;
  }
    
  /*
   * Метод обертка для PDOStatement::fetch()
   * Возвращает одну строку по запроссу
   */
  
  public static function GetRow($sqlQuery, $params = null,
                                $fetchStyle = PDO::FETCH_ASSOC)
  {
    // Задаем по умолчанию возвращаемое значение в NULL
    $result = null;
   
    try{
      
      $database_handler = self::connect();
      
      $statement_handler = $database_handler->prepare($sqlQuery);
      $statement_handler->execute($params);
    
      //Получаем строку
      $result = $statement_handler->fetch($fetchStyle);
      
    }catch(PDOException $e){
      
      self::Close();
      trigger_error($e->getMessage(), E_USER_ERROR);
    }
    
    return $result;
  }
  
  /*
   * Метот котрый возвращает одно значение по
   * заданному запроссу...
   */
  
  public static function GetOne($sqlQuery, $params = null){
   
    $result = null;

    try{
     
      $database_handler = self::connect();
    
      $statement_handler = $database_handler->prepare($sqlQuery);
      $statement_handler->execute($params);
     
      $result = $statement_handler->fetch(PDO::FETCH_NUM);
      $result = $result[0];
    }catch(PDOException $e){
      
      self::Close();
      trigger_error($e->getMessage(), E_USER_ERROR);
    }
    return $result;
  }  
  
  /*
   *Метод который проверяет запросс на валидность... 
   */
  
  public static function quote($string){
      
      $result = null;

    try{
     
      $database_handler = self::connect();
    
      $result = $database_handler->quote($string);
    }catch(PDOException $e){
      
      self::Close();
      trigger_error($e->getMessage(), E_USER_ERROR);
    }
    return $result;
  }
  
  /*
   * Метод который возвращает последний добавленый номер 
   * в базу данных...
   * 
   */
  
  public static function lastInsertId(){

      $result = null;

    try{
     
      $database_handler = self::connect();
    
      $result = $database_handler->lastInsertId();
    }catch(PDOException $e){
      
      self::Close();
      trigger_error($e->getMessage(), E_USER_ERROR);
    }
    return $result;
       
  }
}

?>

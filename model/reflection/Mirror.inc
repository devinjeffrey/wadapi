<?php 
	class Mirror{
		//Array of previously reflected classes
		private static $reflectedClasses = array();
		
		//Array of previously reflected properties
		private static $reflectedProperties = array();
		
		//Array of previously reflected annotations
		private static $reflectedAnnotations = array();
		
		public static function reflectClass($class){
			$reflectedClass = null;
		
			if(is_object($class)){
				$class = get_class($class);
			}
			
			if(self::validateClass($class)){
				if(array_key_exists($class, self::$reflectedClasses)){
					$reflectedClass = self::$reflectedClasses[$class];
				}else{
					$reflectedClass = new WadadliReflectionClass($class);
					self::$reflectedClasses[$class] = $reflectedClass;
				}
			}
			
			return $reflectedClass;
		}
		
		public static function reflectProperty($class, $property){
			$reflectedProperty = null;
		
			if(is_object($class)){
				$class = get_class($class);
			}
			
			if(self::validateClass($class)){
				if(!is_string($property)){
					if(is_object($property)){
						$type = "object";
					}else{
						$type = gettype($property);
					}
					
					fatal_error(UNEXPECTED_ARGUMENT_WARNING,"Mirror expects property to be a string, $type given.");
					return;
				}
				
				if(!array_key_exists($class,self::$reflectedProperties)){
					self::$reflectedProperties[$class] = array();
				}
				
				if(!array_key_exists($property,self::$reflectedProperties[$class])){
					try{
						$reflectedProperty = new WadadliReflectionProperty($class,$property);
					}catch(ReflectionException $re){
						fatal_error(UNEXPECTED_ARGUMENT_WARNING,
								"Property '$property' of class '$class' does not exist and cannot be reflected.");
						return;
					}
					
					self::$reflectedProperties[$class][$property] = $reflectedProperty;
				}else{
					$reflectedProperty = self::$reflectedProperties[$class][$property];
				}
			}
			
			return $reflectedProperty;
		}
		
		private static function validateClass($class){			
			if(!is_string($class)){
				$type = gettype($class);
				fatal_error(UNEXPECTED_ARGUMENT_WARNING,"Mirror expects class to be a string or object, $type given.");
				return false;
			}
			
			if(is_string($class) && !class_exists($class)){
				fatal_error(UNEXPECTED_ARGUMENT_WARNING,"Class '$class' does not exist and cannot be reflected.");
				return false;
			}
			
			return true;
		}
	}
?>
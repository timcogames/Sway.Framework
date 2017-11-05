#ifndef SWAY_FOUNDATION_DECLAREOBJECTMACROS_H
#define SWAY_FOUNDATION_DECLAREOBJECTMACROS_H

#define DECLARE_OBJECT(TClass, TSuperClass)                                                                                \
	public:                                                                                                                \
	typedef TSuperClass Super;                                                                                             \
	static const sway::foundation::ObjectMetadata *getObjectMetadata() {                                                   \
		static const sway::foundation::ObjectMetadata metadata(#TClass, Super::getObjectMetadata());                       \
		return &metadata;                                                                                                  \
	}                                                                                                                      \
	virtual const sway::foundation::ObjectMetadata *getSuperclass() const { return getObjectMetadata()->getSuperclass(); } \
	virtual const std::string &getClassName() const { return getObjectMetadata()->getClassName(); }

#endif // SWAY_FOUNDATION_DECLAREOBJECTMACROS_H